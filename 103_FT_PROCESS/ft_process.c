/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:17:22 by lumugot           #+#    #+#             */
/*   Updated: 2025/07/17 15:07:51 by lumugot          ###   ########.fr       */
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

	*o = (t_obj *)head;
	*(o + 1) = NULL;
	ft_new_vec(**tmp, INFINITY, INFINITY, INFINITY);
	while (*o)
	{
		ft_cpy_ray(*(tmp + 1), ray);
		if ((*o)->hit(*o, *(tmp + 1)))
		{
			if (ft_vec_dist(**(tmp + 1), *ray) < ft_vec_dist(**tmp, *ray))
			{
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

	ft_vec_add(dir, vp->pos, *scaled);
	ft_vec_add(dir, dir, *(scaled + 1));
	ft_vec_sub(dir, dir, scene->camera.pos);
	ft_new_ray(ray, scene->camera.pos, dir);
}

static inline void	ft_put_color(t_mlx_obj *mobj,
	int iter[2], unsigned int color)
{
	*(unsigned int *)(mobj->img_data + (*iter * mobj->size_line
				+ *(iter + 1) * (mobj->bpp / 8))) = color;
}

void	ft_process(t_mlx_obj *mobj, const t_viewport *vp,
	t_scene *s, const t_rules *r)
{
	t_obj	*hit;
	t_vec	scaled[2];
	double	pixel[2];
	int		i[2];

	*pixel = 1.0 / mobj->win_i;
	*(pixel + 1) = 1.0 / mobj->win_j;
	*(i + 1) = 0;
	while (*(i + 1) < mobj->win_i)
	{
		ft_vec_scale(*scaled, vp->hor, (*(i + 1) + .5) * *pixel);
		*i = 0;
		while (*i < mobj->win_j)
		{
			ft_vec_scale(*(scaled + 1), vp->ver, (*i + .5) * *(pixel + 1));
			ft_shoot_ray(s->ray, vp, s, scaled);
			hit = ft_hit_nearest_obj(s->ray, s->objects);
			if (!hit)
				ft_put_color(mobj, i, 0xc5eff0 * (r->coloration == ft_unicorn));
			else
				ft_put_color(mobj, i, r->coloration(s->ray, hit, s, r));
			(*i) += r->pixel_cross;
		}
		(*(i + 1)) += r->pixel_cross;
	}
}
