/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:13:33 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/06/02 19:13:34 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_process.h"

/*
Tries to hit every single object and get the nearest one.
On hit, returns the index of the nearest object and edits the incoming ray.
Else returns -1.
*i = iterator.
*(i + 1) = nearest_object_index.
*tmp = outray.
*(tmp + 1) = tmpray.
*/
static int	ft_hit_nearest_obj(t_ray ray, const t_obj *all)
{
	t_ray	tmp[2];
	int		i[2];

	*i = -1;
	*(i + 1) = -1;
	ft_new_vec(**tmp, inf, inf, inf);
	while (*(all + ++*i))
	{
		ft_cpy_ray(*(tmp + 1), ray);
		if ((*(all + *i)).hit(*(all + *i), *(tmp + 1)))
		{
			if (ft_vec_dist(**(tmp + 1), ray) < ft_vec_dist(**tmp, ray))
			{
				*(i + 1) = *i;
				ft_cpy_ray(*tmp, *(tmp + 1));
			}
		}
	}
	if (***tmp != inf)
		ft_cpy_ray(ray, *tmp);
	return (*(i + 1));
}

static void	ft_blend_color(t_ray hit_ray, const t_obj *all, int hit)
{
	t_color		color;
	t_color		reflect;
	const t_ray	init_ray = hit_ray;
	char		depth;
	float		mult;

	ft_memcpy(color, (*(all + hit)).color, 3);
	doshadowthings(hit_ray, all); // Create a function for that
	ft_cpy_ray(hit_ray, init_ray);
	mult = .33f;
	depth = -1;
	while (++depth < 4)
	{
		hit = ft_hit_nearest_obj(hit_ray, all);
		if (hit < 0)
			break ;
		ft_color_reflect(reflect, (*(all + hit)).color, mult);
		ft_color_add(color, reflect);
		mult *= .75f;
	}
	print_color(color); // will print to actual focused pixel :P
}

void	ft_process(t_ray ray, const t_obj *all)
{
	int	hit_index;

	while (cross_pixel()) // not set too but will :D
	{
		hit_index = ft_hit_nearest_obj(ray, all);
		if (hit_index < 0)
			print_color(NULL); // will print ambient color d..b
		else
			ft_blend_color(ray, all, hit_index);
	}
}
