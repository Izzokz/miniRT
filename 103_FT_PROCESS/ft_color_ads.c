/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_ads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:15:43 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/04 14:41:38 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

inline static void	ft_color_mult(t_color edit, const t_color m1,
	const t_color m2)
{
	*edit = *m1 * *m2;
	*(edit + 1) = *(m1 + 1) * *(m2 + 1);
	*(edit + 2) = *(m1 + 2) * *(m2 + 2);
}

void	ft_color_ads(t_color edit, const t_scene *scene, const t_obj *hit)
{
	t_color	ambient;
	t_color	diffuse[2];
	t_color	specular;
	t_ray	tmp;
	t_obj	*light;

	ft_color_mult(ambient, scene->ambient_light.color, hit->color);
	*diffuse = (t_color){0, 0, 0};
	light = scene->lights;
	while (light)
	{
		ft_new_ray(tmp, *scene->ray, light->pos);
		ft_color_mult(*(diffuse + 1), hit->color, light->color);
		ft_color_mult(*(diffuse + 1), *(diffuse + 1),
			ft_pos_val(ft_vec_dot(*(scene->ray + 1), *(tmp + 1))));
		ft_color_add(*diffuse, *(diffuse + 1));
	}
	ft_color_scale(specular, light->color,
		ft_pow(ft_pos_val(ft_vec_dot(/*complete*/)),
			light->brightness));
	edit = ambient + diffuse + specular;
}
