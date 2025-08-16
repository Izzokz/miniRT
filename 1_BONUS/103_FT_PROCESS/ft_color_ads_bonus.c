/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_ads_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:15:43 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/11 18:35:08 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

/*
tmp[0] = percentage
tmp[1] = attenuation
tmp[2] = random vector
*/
inline void	ft_color_light_dist(t_color edit,
	const t_light *light, const t_vec oray[2], const t_scene *scene)
{
	static const float	f[3] = {.5, .1, .016};
	double				tmp[5];
	t_ray				shadow_tester;
	t_obj				*hit;
	unsigned char		i;

	tmp[0] = 0;
	i = -1;
	while (++i < MRT_SHADOW_SAMPLES)
	{
		ft_vec_offset(shadow_tester[0], oray[0], oray[1], EPSILON);
		ft_vec_random_sphere(tmp + 2, light->pos);
		ft_ray_dir(shadow_tester, tmp + 2);
		hit = ft_hit_nearest_obj_nb(shadow_tester, scene->objects);
		if (!hit || ft_vec_dist(shadow_tester[0], hit->params)
			> ft_vec_dist(shadow_tester[0], light->pos))
			tmp[0] += 1;
	}
	tmp[0] = tmp[0] / MRT_SHADOW_SAMPLES;
	ft_memcpy(edit, light->color, 3);
	tmp[1] = ft_vec_dist(oray[0], light->pos);
	tmp[1] = 1.0 / (f[0] + f[1] * tmp[1] + f[2] * pow(tmp[1], 2));
	ft_color_scale(edit, light->brightness * tmp[0] * tmp[1]
		* ft_get_lambert(oray, light->pos));
}

/*
tmp = hit_pos to light (ray)
tmp[2] = normal
*/
static void	ft_color_ads(t_color edit, const t_scene *scene, const t_obj *hit)
{
	t_color_ads	ads;
	t_vec		tmp[3];
	t_light		*light;

	ft_memset(&ads, 0, sizeof(t_color_ads));
	ft_color_mult(ads.ambient, hit->color, scene->ambient_light.color);
	ft_color_scale(ads.ambient, scene->ambient_light.ratio);
	light = scene->lights;
	while (light)
	{
		ft_new_ray(tmp, scene->ray[0], light->pos);
		ft_color_light_dist(ads.diffuse[1], light, tmp, scene);
		ft_color_mult(ads.diffuse[1], ads.diffuse[1], hit->color);
		ft_obj_normal(hit, scene->ray[0], tmp[2], scene->ray[1]);
		ft_color_scale(ads.diffuse[1], fmax(0, ft_vec_dot(tmp[2], tmp[1])));
		ft_color_add(ads.diffuse[0], ads.diffuse[1]);
		ft_color_add(ads.specular[1], ads.specular[0]);
		light = light->next;
	}
	ft_color_merge(edit, ads.ambient, ads.diffuse[0], ads.specular[1]);
}

inline void	ft_color_fix(t_color edit)
{
	float	exposure;
	float	gamma;
	float	c;
	char	i;

	exposure = 1.5f;
	gamma = 2.2f;
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

unsigned int	ft_blend_color(t_ray hit_ray, t_obj *hit, t_scene *scene,
	const t_rules *rules)
{
	t_color	color;
	t_color	reflect;
	t_color	bounce;
	char	iter;

	ft_memset(color, 0, 3);
	ft_memset(bounce, 0, 3);
	scene->mult = rules->ref_str;
	ft_color_ads(color, scene, hit);
	iter = -1;
	while (++iter < rules->ref)
	{
		hit = ft_hit_nearest_obj(hit_ray, scene->objects);
		if (!hit)
			break ;
		ft_color_ads(bounce, scene, hit);
		ft_color_reflect(reflect, bounce, scene->mult);
		ft_color_add(color, reflect);
		scene->mult *= .5f;
	}
	ft_color_fix(color);
	return (ft_convert_color(color));
}
