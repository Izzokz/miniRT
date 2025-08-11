/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_glass.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:15:43 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/11 22:24:05 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
*hit = hit_to_light
*(hit + 1) = hit (just after hit (no modification))
*/
static inline void	ft_blinn_phong_bug(t_color specular, const t_scene *scene,
	const t_ray hit[2], const t_light light)
{
	t_ray	cam_to_hit;
	t_vec	halfway;
	double	spec;

	ft_new_ray(cam_to_hit, scene->camera.pos, **hit);
	ft_vec_add(halfway, *(*hit + 1), *(cam_to_hit + 1));
	ft_vec_norm(halfway, halfway);
	spec = ft_vec_dot(*(*(hit + 1) + 1), halfway);
	if (spec < 0)
		spec = 0;
	else
		spec = pow(spec, light.brightness);
	ft_color_light_dist(specular, light, *(hit + 1), scene);
	ft_color_scale(specular, spec);
}

void	ft_color_ads_bug(t_color edit, const t_scene *scene, const t_obj *hit)
{
	t_color_ads	ads;
	t_ray		tmp;
	t_ray		cat[2];

	ft_color_mult(ads.ambient, hit->color, scene->ambient_light.color);
	ft_color_scale(ads.ambient, scene->ambient_light.ratio);
	ft_memset(*(ads.diffuse), 0, 3);
	ft_memset(*ads.specular, 0, 3);
	ft_memset(*(ads.specular + 1), 0, 3);
	if (scene->light.is_set)
	{
		ft_new_ray(tmp, *scene->ray, scene->light.pos);
		ft_color_light_dist(*(ads.diffuse + 1), scene->light, tmp, scene);
		ft_color_mult(*(ads.diffuse + 1), *(ads.diffuse + 1), hit->color);
		ft_color_scale(*(ads.diffuse + 1),
			fmax(0, ft_vec_dot(*(scene->ray + 1), *(tmp + 1))));
		ft_color_add(*(ads.diffuse), *(ads.diffuse + 1));
		ft_store(cat, tmp, scene->ray);
		ft_blinn_phong_bug(*(ads.specular), scene, cat, scene->light);
		ft_color_add(*(ads.specular + 1), *(ads.specular));
	}
	ft_color_merge(edit, ads.ambient, *(ads.diffuse), *(ads.specular + 1));
}

unsigned int	ft_color_glass(t_ray hit_ray, t_obj *hit, t_scene *scene,
	const t_rules *rules)
{
	t_color	color;
	t_color	reflect;
	t_color	bounce;
	char	iter;
	float	mult;

	ft_memset(color, 0, 3);
	ft_color_ads_bug(color, scene, hit);
	mult = rules->ref_str;
	iter = -1;
	while (++iter < rules->ref)
	{
		hit = ft_hit_nearest_obj(hit_ray, scene->objects);
		if (!hit)
			break ;
		ft_memset(bounce, 0, 3);
		ft_color_ads_bug(bounce, scene, hit);
		ft_color_reflect(reflect, bounce, mult);
		ft_color_add(color, reflect);
		mult *= .75f;
	}
	ft_color_fix(color);
	return (ft_convert_color(color));
}
