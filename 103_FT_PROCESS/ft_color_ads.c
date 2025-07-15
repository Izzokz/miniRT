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
/*
static inline void	ft_blinn_phong(t_color specular, const t_scene *scene,
	const t_ray hit[2], const t_light *light)
{
	t_ray	cam_to_hit;
	t_vec	halfway;
	double	spec;

	ft_new_ray(cam_to_hit, scene->camera.pos, **hit);
	ft_vec_add(halfway, *(*hit + 1), *(cam_to_hit + 1));
	ft_vec_norm(halfway, halfway);
	spec = ft_vec_dot(*(*(hit + 1) + 1), *(*hit + 1));
	if (spec < 0)
		spec = 0;
	else
		spec = pow(spec, light->brightness);
	*specular = *light->color * spec;
	*(specular + 1) = *(light->color + 1) * spec;
	*(specular + 2) = *(light->color + 2) * spec;
}
*/
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

	ft_color_mult(ads.ambient, hit->color, scene->ambient_light.color);
	ft_color_scale(ads.ambient, scene->ambient_light.ratio);
	ft_memset(*(ads.diffuse), 0, 3);
	ft_memset(*ads.specular, 0, 3);
	ft_memset(*(ads.specular + 1), 0, 3);
	light = scene->lights;
	while (light)
	{
		ft_new_ray(tmp, *scene->ray, light->pos);
		ft_color_mult(*(ads.diffuse + 1), light->color, hit->color);
		ft_color_scale(*(ads.diffuse + 1),
			ft_pos_val(ft_vec_dot(*(scene->ray + 1), *(tmp + 1))));
		ft_color_add(*(ads.diffuse), *(ads.diffuse + 1));
		ft_store(cat, tmp, scene->ray);
		//ft_blinn_phong(*(ads.specular), scene, cat, light);
		//ft_color_add(*(ads.specular + 1), *(ads.specular));
		light = light->next;
	}
	ft_color_merge(edit, ads.ambient, *(ads.diffuse), *(ads.specular + 1));
}

static inline void	ft_shadow(t_color color, t_vec pos, const t_scene *scene)
{
	t_ray	ray;
	t_light	*light;
	t_obj	*hit;

	light = scene->lights;
	while (light)
	{
		ft_new_ray(ray, pos, light->pos);
		hit = ft_hit_nearest_obj(ray, scene->objects);
		if (hit && ft_vec_dist(pos, hit->params) < ft_vec_dist(pos, light->pos))
			ft_color_scale(color, .666f);
		light = light->next;
	}
}

static inline void	ft_color_fix(t_color edit)
{
	float	exposure;
	float	gamma;
	float	c;
	char	i;

	exposure = 3.f;
	gamma = 1.1f;
	i = -1;
	while (++i < 3)
	{
		c = *(edit + i) / 255.0f;
		c = 1.0f - expf(-exposure * c);
		c = pow(c, 1.0f / gamma);
		if (c < 0)
			c = 0;
		else if (c > 1)
			c = 1;
		*(edit + i) = (unsigned char)(c * 255.0f + .5f);
	}
}

unsigned int	ft_blend_color(t_ray hit_ray, t_obj *hit, const t_scene *scene,
	const t_rules *rules)
{
	t_color	color;
	t_color	reflect;
	t_color	bounce;
	char	depth;
	float	mult;

	ft_memset(color, 0, 3);
	ft_color_ads(color, scene, hit);
	ft_shadow(color, *hit_ray, scene);
	mult = rules->ref_str;
	depth = -1;
	while (++depth < rules->ref)
	{
		hit = ft_hit_nearest_obj(hit_ray, scene->objects);
		if (!hit)
			break ;
		ft_memcpy(bounce, hit->color, 3);
		ft_color_ads(bounce, scene, hit);
		ft_shadow(bounce, *hit_ray, scene);
		ft_color_reflect(reflect, bounce, mult);
		ft_color_add(color, reflect);
		mult *= .75f;
	}
	ft_color_fix(color);
	return (ft_convert_color(color));
}
