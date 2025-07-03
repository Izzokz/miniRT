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
On hit, returns the nearest object and edits the incoming ray.
Else returns NULL.
*o = tmp object (iteration).
*(o + 1) = nearest object.
*tmp = outray.
*(tmp + 1) = tmpray.
*/
static int	ft_hit_nearest_obj(t_ray ray, const t_obj *head)
{
	t_ray	tmp[2];
	t_obj	*o[2];

	*o = head;
	*(o + 1) = NULL;
	ft_new_vec(**tmp, inf, inf, inf);
	while (*o)
	{
		ft_cpy_ray(*(tmp + 1), ray);
		if ((*o).hit(*o, *(tmp + 1)))
		{
			if (ft_vec_dist(**(tmp + 1), ray) < ft_vec_dist(**tmp, ray))
			{
				*(o + 1) = *o;
				ft_cpy_ray(*tmp, *(tmp + 1));
			}
		}
		*o = (*o)->next;
	}
	if (***tmp != inf)
		ft_cpy_ray(ray, *tmp);
	return (*(o + 1));
}

static void	ft_shadow(t_color color, t_vec pos, const t_scene *scene)
{
	t_ray	ray;
	t_light	*light;

	light = scene->lights;
	while (light)
	{
		ft_new_ray(ray, pos, light->pos));
		if (ft_hit_nearest_obj(ray, scene->objects))
			ft_color_scale(color, .66f);
		light = light->next;
	}
}

static void	ft_blend_color(t_ray hit_ray, const t_scene *scene, t_obj *hit)
{
	t_color	color;
	t_color	reflect;
	char	depth;
	float	mult;

	// calculate (ambient + diffuse + specular)
	ft_memcpy(color, hit->color, 3);
	ft_shadow(color, *hit_ray, scene);
	mult = .33f;
	depth = -1;
	while (++depth < 4)
	{
		hit = ft_hit_nearest_obj(hit_ray, scene->objects);
		if (!hit)
			break ;
		// calculate (ambient + diffuse + specular)
		ft_color_reflect(reflect, hit->color, mult);
		ft_shadow(reflect, *hit_ray, scene);
		ft_color_add(color, reflect);
		mult *= .75f;
	}
	print_color(color); // will print to actual focused pixel :P
}

void	ft_process(t_mlx_obj *mlx, const t_viewport vp,
	const t_scene *scene, const t_rules rules)
{
	t_obj	*hit;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			hit = ft_hit_nearest_obj(/* ray */, scene->objects);
			if (!hit)
				print ambient color;
			else
				ft_put_color(/* mlx infos */, rules.coloration(/* ray */, hit, scene, rules));
			j += rules.pixel_cross;
		}
	}
}
