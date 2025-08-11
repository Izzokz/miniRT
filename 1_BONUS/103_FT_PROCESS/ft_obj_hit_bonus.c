/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_hit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:07:42 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/11 18:36:16 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static inline void	ft_init_hit_vars(const t_obj *head, t_ray tmp[2],
	t_obj *objs[2], double *nearest_dist)
{
	objs[0] = (t_obj *)head;
	objs[1] = NULL;
	*nearest_dist = INFINITY;
	ft_new_vec(tmp[0][0], INFINITY, INFINITY, INFINITY);
}

static inline void	ft_update_nearest(double *nearest_dist, double current_dist,
	t_obj *objs[2], t_ray tmp[2])
{
	*nearest_dist = current_dist;
	objs[1] = objs[0];
	ft_cpy_ray(tmp[0], tmp[1]);
}

/*
Tries to hit every single object and get the nearest one.
On hit, returns the nearest object and edits the incoming ray.
Else returns NULL.
o[0] = tmp object (iteration).
o[1] = nearest object.
tmp[0] = outray.
tmp[1] = tmpray.
*/
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
