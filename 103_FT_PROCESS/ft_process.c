/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:17:22 by lumugot           #+#    #+#             */
/*   Updated: 2025/07/31 13:34:28 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
Tries to hit every single object and get the nearest one.
On hit, returns the nearest object and edits the incoming ray.
Else returns NULL.
o[0] = tmp object (iteration).
o[1] = nearest object.
tmp[0] = outray.
tmp[1] = tmpray.
*/
static void	ft_init_hit_vars(const t_obj *head, t_ray tmp[2],
	t_obj *objs[2], double *nearest_dist)
{
	objs[0] = (t_obj *)head;
	objs[1] = NULL;
	*nearest_dist = INFINITY;
	ft_new_vec(tmp[0][0], INFINITY, INFINITY, INFINITY);
}

static void	ft_update_nearest(double *nearest_dist, double current_dist,
	t_obj *objs[2], t_ray tmp[2])
{
	*nearest_dist = current_dist;
	objs[1] = objs[0];
	ft_cpy_ray(tmp[0], tmp[1]);
}

t_obj	*ft_hit_nearest_obj(t_ray ray, const t_obj *head)
{
	t_ray	tmp[2];
	t_obj	*objs[2];
	double	nearest_dist;
	double	current_dist;

	ft_init_hit_vars(head, tmp, objs, &nearest_dist);
	while (objs[0])
	{
		ft_cpy_ray(tmp[1], ray);
		if (objs[0]->hit(objs[0], tmp[1]))
		{
			current_dist = ft_vec_dist(tmp[1][0], ray[0]);
			if (current_dist < nearest_dist)
				ft_update_nearest(&nearest_dist, current_dist, objs, tmp);
		}
		objs[0] = objs[0]->next;
	}
	if (tmp[0][0][0] != INFINITY)
		ft_cpy_ray(ray, tmp[0]);
	return (objs[1]);
}

/*
Same as above, no ray modification (no bounce)
*/
t_obj	*ft_hit_nearest_obj_nb(const t_ray ray, const t_obj *head)
{
	t_ray	tmp[2];
	t_obj	*objs[2];
	double	nearest_dist;
	double	current_dist;

	ft_init_hit_vars(head, tmp, objs, &nearest_dist);
	while (objs[0])
	{
		ft_cpy_ray(tmp[1], ray);
		if (objs[0]->hit(objs[0], tmp[1]))
		{
			current_dist = ft_vec_dist(tmp[1][0], ray[0]);
			if (current_dist < nearest_dist)
				ft_update_nearest(&nearest_dist, current_dist, objs, tmp);
		}
		objs[0] = objs[0]->next;
	}
	return (objs[1]);
}

static inline void	ft_put_color(t_mlx_obj *mobj,
	int x, int y, unsigned int color)
{
	char	*dst;

	dst = mobj->img_data + (y * mobj->size_line + x * (mobj->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	ft_init_up_vec(t_vec up, const t_vec forward)
{
	if (fabs(forward[1]) > 0.99)
		ft_new_vec(up, 0, 0, 1); // g_forward
	else
		ft_new_vec(up, 0, 1, 0); // g_up
}

static void	ft_init_right_up(
	t_vec right, t_vec up, const t_vec forward)
{
	ft_vec_cross(right, up, forward);
	ft_vec_norm(right, right);
	ft_vec_cross(up, forward, right);
	ft_vec_norm(up, up);
}

static void	ft_apply_roll(
	t_vec right, t_vec up, double roll)
{
	double	cr;
	double	sr;
	t_vec	right_rot;
	t_vec	up_rot;

	cr = cos(roll);
	sr = sin(roll);
	right_rot[0] = cr * right[0] - sr * up[0];
	right_rot[1] = cr * right[1] - sr * up[1];
	right_rot[2] = cr * right[2] - sr * up[2];
	up_rot[0] = sr * right[0] + cr * up[0];
	up_rot[1] = sr * right[1] + cr * up[1];
	up_rot[2] = sr * right[2] + cr * up[2];
	ft_cpy_vec(right, right_rot);
	ft_cpy_vec(up, up_rot);
}

static void	ft_init_cam_vectors(t_vec cam_vectors[3], const t_scene *s)
{
	double	win_ratio;
	double	plane_h;
	t_vec	tmp1;
	t_vec	tmp2;

	win_ratio = (double)WIDTH / (double)HEIGHT;
	plane_h = tan(s->camera.fov * 0.5 * (PI / 180.0)) * 2.0;
	ft_cpy_vec(tmp1, s->_forward);
	ft_init_up_vec(tmp2, tmp1);
	ft_init_right_up(cam_vectors[0], tmp2, tmp1);
	ft_apply_roll(cam_vectors[0], tmp2, s->_roll);
	ft_vec_scale(cam_vectors[0], cam_vectors[0], plane_h * win_ratio);
	ft_vec_scale(cam_vectors[1], tmp2, plane_h);
	ft_vec_scale(tmp1, s->_forward, 2.0);
	ft_vec_sub(cam_vectors[2], s->camera.pos, tmp1);
}

static inline void	ft_hit_parse(t_mlx_obj *mobj, int i[2],
	t_scene *s, const t_rules *r)
{
	t_obj	*hit;

	hit = ft_hit_nearest_obj(s->ray, s->objects);
	if (hit)
		return (ft_put_color(mobj, *i, *(i + 1),
				r->coloration(s->ray, hit, s, r)));
	if (r->coloration == ft_unicorn)
		return (ft_put_color(mobj, *i, *(i + 1), 0xdc96ff));
	if (r->coloration == ft_color_virus)
		return (ft_put_color(mobj, *i, *(i + 1), rand()));
	if (r->coloration == ft_color_chill)
		return (ft_put_color(mobj, *i, *(i + 1), 0xcffff9));
	if (r->coloration == ft_color_error)
		return (ft_put_color(mobj, *i, *(i + 1),
				0xff0000 + 255 * (rand() % 2)));
	ft_put_color(mobj, *i, *(i + 1), 0);
}

static void	ft_process_one_pixel(t_mlx_obj *mobj, t_scene *s,
	const t_rules *r, const t_vec cam_vectors[3])
{
	t_obj	*hit;
	t_vec	ray_moves[2];
	t_vec	ray_move;

	ft_vec_scale(ray_moves[0], cam_vectors[0],
		((double)s->coords[0] / WIDTH) - 0.5);
	ft_vec_scale(ray_moves[1], cam_vectors[1],
		-(((double)s->coords[1] / HEIGHT) - 0.5));
	ft_vec_add(ray_move, ray_moves[0], ray_moves[1]);
	ft_vec_add(s->ray[0], s->camera.pos, ray_move);
	ft_vec_sub(s->ray[1], s->ray[0], cam_vectors[2]);
	ft_vec_norm(s->ray[1], s->ray[1]);
	hit = ft_hit_nearest_obj(s->ray, s->objects);
	if (!hit)
		ft_hit_parse(mobj, s->coords, s, r);
	else
		ft_put_color(mobj, s->coords[0], s->coords[1],
			r->coloration(s->ray, hit, s, r));
}

static void	ft_calculate_pixels(t_mlx_obj *mobj, t_scene *s,
	const t_rules *r, const t_vec cam_vectors[3])
{
	s->coords[1] = 0;
	while (s->coords[1] < HEIGHT)
	{
		s->coords[0] = 0;
		while (s->coords[0] < WIDTH)
		{
			ft_process_one_pixel(mobj, s, r, cam_vectors);
			s->coords[0] += r->pixel_cross;
		}
		s->coords[1] += r->pixel_cross;
	}
}

void	ft_process(t_mlx_obj *mobj,
	t_scene *s, const t_rules *r)
{
	t_vec	cam_vectors[3];

	ft_init_cam_vectors(cam_vectors, s);
	ft_calculate_pixels(mobj, s, r, cam_vectors);
}
