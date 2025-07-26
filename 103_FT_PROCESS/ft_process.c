/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:17:22 by lumugot           #+#    #+#             */
/*   Updated: 2025/07/27 01:05:55 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
Tries to hit every single object and get the nearest one.
On hit, returns the nearest object and edits the incoming ray.
Else returns NULL.
*o = tmp object (iteration).
*(o + 1) = nearest object.
*tmp = outray.
*(tmp + 1) = tmpray.
*/
t_obj	*ft_hit_nearest_obj(t_ray ray, const t_obj *head)
{
	t_ray	tmp[2];
	t_obj	*o[2];
	double	nearest_dist;
	double	current_dist;

	*o = (t_obj *)head;
	*(o + 1) = NULL;
	nearest_dist = INFINITY;
	ft_new_vec(**tmp, INFINITY, INFINITY, INFINITY);
	while (*o)
	{
		ft_cpy_ray(*(tmp + 1), ray);
		if ((*o)->hit(*o, *(tmp + 1)))
		{
			current_dist = ft_vec_dist(**(tmp + 1), *ray);
			if (current_dist < nearest_dist)
			{
				nearest_dist = current_dist;
				*(o + 1) = *o;
				ft_cpy_ray(*tmp, *(tmp + 1));
			}
		}
		*o = (*o)->next;
	}
	if (***tmp != INFINITY)
		ft_cpy_ray(ray, *tmp);
	return (*(o + 1));
}

static inline void	ft_shoot_ray(t_ray ray, const t_viewport *vp,
	const t_scene *scene, const t_vec scaled[2])
{
	t_vec	dir;
	t_vec	point_on_viewport;

	ft_vec_add(point_on_viewport, vp->pos, *scaled);
	ft_vec_add(point_on_viewport, point_on_viewport, *(scaled + 1));
	ft_vec_sub(dir, point_on_viewport, scene->camera.pos);
	ft_new_ray(ray, scene->camera.pos, dir);
}

static inline void	ft_put_color(t_mlx_obj *mobj,
	int x, int y, unsigned int color)
{
	char	*dst;

	dst = mobj->img_data + (y * mobj->size_line + x * (mobj->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	ft_init_cam_vectors(t_vec cam_vectors[3], const t_scene *s)
{
	double	win_ratio;
	double	plane_h;
	double	plane_w;
	t_vec	cam_d;

	win_ratio = (double)WIDTH / (double)HEIGHT;
	plane_h = tan(s->camera.fov * 0.5 * (PI / 180.0)) * 2.0;
	plane_w = plane_h * win_ratio;
	ft_vec_scale(cam_vectors[0], s->_right, plane_w);
	ft_vec_scale(cam_vectors[1], s->_up, plane_h);
	ft_vec_scale(cam_d, s->_forward, 2.0);
	ft_vec_sub(cam_vectors[2], s->camera.pos, cam_d);
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
		((double)s->coords[1] / HEIGHT) - 0.5);
	ft_vec_add(ray_move, ray_moves[0], ray_moves[1]);
	ft_vec_add(s->ray[0], s->camera.pos, ray_move);
	ft_vec_sub(s->ray[1], s->ray[0], cam_vectors[2]);
	ft_vec_norm(s->ray[1], s->ray[1]);
	hit = ft_hit_nearest_obj(s->ray, s->objects);
	if (!hit)
		ft_put_color(mobj, s->coords[0], s->coords[1],
			0xc5eff0 * (r->coloration == ft_unicorn));
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

void	ft_process(t_mlx_obj *mobj, const t_viewport *vp,
	t_scene *s, const t_rules *r)
{
	t_vec	cam_vectors[3];

	(void)vp;
	ft_init_cam_vectors(cam_vectors, s);
	ft_calculate_pixels(mobj, s, r, cam_vectors);
}
