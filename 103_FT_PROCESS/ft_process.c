/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:17:22 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/19 13:35:05 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

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

static void	ft_shadow(t_color color, t_vec pos, const t_obj *all)
{
	t_ray	ray;
	int		i;

	i = -1;
	while ((*(all + ++i)).params)
	{
		if ((*(all + i)).type != 'l')
			continue ;
		ft_new_ray(ray, pos, *((*(all + i)).params));
		if (ft_hit_nearest_obj(ray, all) > -1)
			ft_color_scale(color, .66f);
	}
}

static void	ft_blend_color(t_ray hit_ray, const t_obj *all, int hit)
{
	t_color	color;
	t_color	reflect;
	char	depth;
	float	mult;

	// calculate (ambient + diffuse + specular)
	ft_memcpy(color, (*(all + hit)).color, 3);
	ft_shadow(color, *hit_ray, all);
	mult = .33f;
	depth = -1;
	while (++depth < 4)
	{
		hit = ft_hit_nearest_obj(hit_ray, all);
		if (hit < 0)
			break ;
		// calculate (ambient + diffuse + specular)
		ft_color_reflect(reflect, (*(all + hit)).color, mult);
		ft_shadow(reflect, *hit_ray, all);
		ft_color_add(color, reflect);
		mult *= .75f;
	}
	print_color(color); // will print to actual focused pixel :P
}

void	ft_process(t_ray ray, const t_obj *all)
{
	int	hit_index;

	while (cross_pixel()) // not set too but will be :D
	{
		hit_index = ft_hit_nearest_obj(ray, all);
		if (hit_index < 0)
			print_color(NULL); // will print ambient color d..b
		else
			ft_blend_color(ray, all, hit_index);
	}
}