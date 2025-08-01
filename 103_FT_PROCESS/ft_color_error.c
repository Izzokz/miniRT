/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:15:43 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/31 19:01:28 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline void	ft_vec_offset(t_vec newv, const t_vec v1,
	const t_vec v2, const double epsilon)
{
	ft_new_vec(newv, *v1 + *v2 * epsilon, *(v1 + 1)
		+ *(v2 + 1) * epsilon, *(v1 + 2) + *(v2 + 2) * epsilon);
}

static inline void	ft_vec_random_sphere(t_vec random, const t_vec lpos)
{
	double	u;
	double	v;
	double	phi;

	u = (double)rand() / ((double)RAND_MAX + 1);
	v = (double)rand() / ((double)RAND_MAX + 1);
	phi = acos(2.0 * v - 1);
	ft_new_vec(random, 2.0 * PI * u, phi, sin(phi));
	ft_vec_scale(random, random, MRT_LIGHT_RADIUS);
	ft_vec_add(random, random, lpos);
}

/*
*tmp = visibility;
*(tmp + 1) = attenuation;
tmp + 2 = random vector;
*/
static inline void	ft_color_light_dist(t_color edit,
	const t_light *light, const t_ray oray, const t_scene *scene)
{
	const float		factors[3] = {.5, .1, .016};
	double			tmp[5];
	t_ray			shadow_tester;
	t_obj			*hit;
	unsigned char	i;

	*tmp = 0;
	i = -1;
	while (++i < MRT_SHADOW_SAMPLES)
	{
		ft_vec_offset(*shadow_tester, *oray, *(oray + 1), 1e-3);
		ft_vec_random_sphere(tmp + 2, light->pos);
		ft_ray_dir(shadow_tester, tmp + 2);
		hit = ft_hit_nearest_obj(shadow_tester, scene->objects);
		if (!hit || ft_vec_dist(*shadow_tester, hit->params)
			>= ft_vec_dist(*shadow_tester, light->pos))
			*tmp += 1;
	}
	*tmp /= MRT_SHADOW_SAMPLES;
	ft_memcpy(edit, light->color, 3);
	*(tmp + 1) = ft_vec_dist(light->pos, *oray);
	*(tmp + 1) = 1.0 / (*factors + *(factors + 1) * *(tmp + 1)
			+ *(factors + 2) * pow(*(tmp + 1), 2));
	ft_color_scale(edit, light->brightness * *tmp * *(tmp + 1));
}

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

	ft_new_ray(cam_to_hit, scene->camera.pos, **hit);
	ft_vec_add(halfway, *(*hit + 1), *(cam_to_hit + 1));
	ft_vec_norm(halfway, halfway);
	spec = ft_vec_dot(*(*(hit + 1) + 1), halfway);
	if (spec < 0)
		spec = 0;
	else
		spec = pow(spec, light->brightness);
	ft_color_light_dist(specular, light, *(hit + 1), scene);
	ft_color_scale(specular, spec);
}

static inline void	ft_color_merge(t_color edit, const t_color ambient,
	const t_color diffuse, const t_color specular)
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
	ft_memset(ads.diffuse[0], 0, 3);
	ft_memset(ads.specular[0], 0, 3);
	ft_memset(ads.specular[1], 0, 3);
	light = scene->lights;
	while (light)
	{
		ft_new_ray(tmp, *scene->ray, light->pos);
		ft_color_light_dist(ads.diffuse[1], light, tmp, scene);
		ft_color_mult(ads.diffuse[1], ads.diffuse[1], hit->color);
		ft_color_scale(ads.diffuse[1],
			fmax(0, ft_vec_dot(scene->ray[1], tmp[1])));
		ft_color_add(ads.diffuse[0], ads.diffuse[1]);
		ft_store(cat, tmp, scene->ray);
		ft_blinn_phong(ads.specular[0], scene, cat, light);
		ft_color_add(ads.specular[1], ads.specular[0]);
		light = light->next;
	}
	ft_color_merge(edit, ads.ambient, ads.diffuse[0], ads.specular[1]);
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

static inline void	ft_error_the_color(t_color edit, const t_color origin,
	const float bfactor)
{
	static const t_color	error = {207, 255, 249};
	t_vec					tmp;

	*tmp = (double)*origin / 255;
	*(tmp + 1) = (double)*(origin + 1) / 255;
	*(tmp + 2) = (double)*(origin + 2) / 255;
	*tmp = fmin(1.0, *tmp * .6 + .4 + .1 * sin(*(tmp + 1) * 5));
	*(tmp + 1) = fmin(1.0, *(tmp + 1) * .6 + .4 + .05 * cos(*tmp * 7));
	*(tmp + 2) = fmin(1.0, *(tmp + 2) * .6 + .4 + .1 * sin(*(tmp + 2) * 3));
	*edit = (1.0f - bfactor) * *origin
		+ bfactor * (.7 * *tmp * 255.0f + .3f * *error);
	*(edit + 1) = (1.0f - bfactor) * *(origin + 1)
		+ bfactor * (.7 * *(tmp + 1) * 255.0f + .3f * *(error + 1));
	*(edit + 2) = (1.0f - bfactor) * *(origin + 2)
		+ bfactor * (.7 * *(tmp + 2) * 255.0f + .3f * *(error + 2));
}

unsigned int	ft_color_error(t_ray hit_ray, t_obj *hit, const t_scene *scene,
	const t_rules *rules)
{
	t_color	color;
	t_color	reflect;
	t_color	bounce;
	char	iter;
	float	mult;

	ft_memset(color, 0, 3);
	ft_color_ads(color, scene, hit);
	mult = rules->ref_str;
	iter = -1;
	while (++iter < rules->ref)
	{
		hit = ft_hit_nearest_obj(hit_ray, scene->objects);
		if (!hit)
			break ;
		ft_memset(bounce, 0, 3);
		ft_color_ads(bounce, scene, hit);
		ft_color_reflect(reflect, bounce, mult);
		ft_color_add(color, reflect);
		mult *= .75f;
	}
	ft_color_fix(color);
	ft_error_the_color(color, color, 6.9);
	return (ft_convert_color(color));
}
