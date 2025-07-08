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

/*
*hit = hit_to_light
*(hit + 1) = hit (just after hit (no modification))
*/
static inline void	ft_blinn_phong(t_color specular, const t_scene *scene,
	const t_ray hit[2], const t_light *light)
{
	t_ray	cam_to_hit;
	t_vec	halfway;
	double	spec;

	ft_new_ray(cam_to_hit, scene->camera.pos, **(t_ray *)(void *)hit);
	ft_vec_add(halfway, *(*(t_ray *)(void *)hit + 1), *(cam_to_hit + 1));
	ft_vec_norm(halfway, halfway);
	spec = ft_vec_dot(*(*((t_ray *)(void *)hit + 1) + 1), halfway);
	if (spec < 0)
		spec = 0;
	spec = pow(spec, light->brightness);
	ft_color_mult(specular, specular, light->color);
}

static inline void	ft_color_merge(t_color edit, t_color ambient,
	t_color diffuse, t_color specular)
{
	ft_color_add(edit, ambient);
	ft_color_add(edit, diffuse);
	ft_color_add(edit, specular);
}

static inline void	ft_store(t_ray cat[2], const t_ray r1, const t_ray r2)
{
	ft_memcpy(cat[0], r1, sizeof(t_ray));	
	ft_memcpy(cat[1], r2, sizeof(t_ray));
}

static void	ft_color_ads(t_color edit, const t_scene *scene, const t_obj *hit)
{
	t_color_ads	ads;
	t_ray		tmp;
	t_ray		cat[2];
	t_light		*light;

	ft_memcpy(ads.ambient, scene->ambient_light.color, 3);
	ft_color_scale(ads.ambient, scene->ambient_light.ratio);
	ft_color_mult(ads.ambient, ads.ambient, hit->color);
	ft_memset(*(ads.diffuse), 0, 3);
	ft_memset(*ads.specular, 0, 3);
	ft_memset(*(ads.specular + 1), 0, 3);
	light = scene->lights;
	while (light)
	{
		ft_new_ray(tmp, *scene->ray, light->pos);
		ft_color_mult(*(ads.diffuse + 1), hit->color, light->color);
		ft_color_scale(*(ads.diffuse + 1),
			ft_pos_val(ft_vec_dot(*(scene->ray + 1), *(tmp + 1))));
		ft_color_add(*(ads.diffuse), *(ads.diffuse + 1));
		ft_store(cat, tmp, scene->ray);
		ft_blinn_phong(*(ads.specular), scene, cat, light);
		ft_color_mult(*(ads.specular), *(ads.specular), light->color);
		ft_color_add(*(ads.specular + 1), *(ads.specular));
		light = light->next;
	}
	ft_color_merge(edit, ads.ambient, *(ads.diffuse), *(ads.specular + 1));
}

static inline void	ft_shadow(t_color color, t_vec pos, const t_scene *scene)
{
	t_ray	ray;
	t_light	*light;

	light = scene->lights;
	while (light)
	{
		ft_new_ray(ray, pos, light->pos);
		if (ft_hit_nearest_obj(ray, scene->objects))
			ft_color_scale(color, .666f);
		light = light->next;
	}
}

unsigned int	ft_blend_color(t_ray hit_ray, t_obj *hit, const t_scene *scene,
	const t_rules *rules)
{
	t_color	color;
	t_color	reflect;
	char	depth;
	float	mult;

	ft_memcpy(color, hit->color, 3);
	ft_color_ads(color, scene, hit);
	ft_shadow(color, *hit_ray, scene);
	mult = rules->ref_str;
	depth = -1;
	while (++depth < rules->ref)
	{
		hit = ft_hit_nearest_obj(hit_ray, scene->objects);
		if (!hit)
			break ;
		ft_color_ads(color, scene, hit);
		ft_color_reflect(reflect, hit->color, mult);
		ft_shadow(reflect, *hit_ray, scene);
		ft_color_add(color, reflect);
		mult *= .75f;
	}
	return (ft_convert_color(color));
}
