/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_ads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:15:43 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/05 16:12:39 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline void	ft_vec_offset(t_vec newv, const t_vec v1,
	const t_vec v2, const double epsilon)
{
	ft_new_vec(newv, v1[0] + v2[0] * epsilon, v1[1]
		+ v2[1] * epsilon, v1[2] + v2[2] * epsilon);
}

static inline void	ft_vec_random_sphere(t_vec random, const t_vec lpos)
{
	double	percent;

	percent = (double)(ft_rand() % 101) / 100;
	random[0] = ((double)(ft_rand() % 201) - 100) / 100;
	random[1] = ((double)(ft_rand() % 201) - 100) / 100;
	random[2] = ((double)(ft_rand() % 201) - 100) / 100;
	ft_vec_scale(random, random, MRT_LIGHT_RADIUS * percent);
	ft_vec_add(random, lpos, random);
}

// static inline double	ft_get_lambert(const t_ray hit, const t_vec dir)
// {
// 	t_ray	ray;
// 	double	dot;

// 	ft_new_ray(ray, *hit, dir);
// 	dot = ft_vec_dot(*(hit + 1), *(ray + 1));
// 	return (dot * (dot >= 0));
// }


static inline void	ft_color_light_dist(t_color edit,
	const t_light *light, const t_ray oray, const t_scene *scene)
{
	static 			const float factors[3] = {.5, .1, .016};
	double 			tmp[5];
	t_ray 			shadow_tester;
	t_obj 			*hit;
	unsigned char	i;

	tmp[0] = 0;
	i = -1;
	while (++i < MRT_SHADOW_SAMPLES)
	{
		ft_vec_offset(shadow_tester[0], oray[0], oray[1], 1e-4);
		ft_vec_random_sphere(tmp + 2, light->pos);
		ft_ray_dir(shadow_tester, tmp + 2);
		hit = ft_hit_nearest_obj_nb(shadow_tester, scene->objects);
		if (!hit || ft_vec_dist(shadow_tester[0], hit->params)
			> ft_vec_dist(shadow_tester[0], light->pos))
			tmp[0] += 1;
	}
	ft_memcpy(edit, light->color, 3);
	tmp[1] = ft_vec_dist(light->pos, oray[0]);
	tmp[1] = 1.0 / (factors[0] + factors[1] * tmp[1] + factors[2] * pow(tmp[1], 2));
	ft_color_scale(edit, light->brightness * tmp[0] * tmp[1]);
}

/*
hit[0] = hit_to_light
hit[1] = hit (just after hit (no modification))
*/
static inline void	ft_blinn_phong(t_color specular, const t_scene *scene,
	const t_ray hit[2], const t_light *light)
{
	t_ray	cam_to_hit;
	t_vec	halfway;
	double	spec;

	ft_new_ray(cam_to_hit, scene->camera.pos, hit[0][0]);
	ft_vec_add(halfway, hit[0][1], cam_to_hit[1]);
	ft_vec_norm(halfway, halfway);
	spec = ft_vec_dot(hit[1][1], halfway);
	if (spec < 0)
		spec = 0;
	else
		spec = pow(spec, PHONG_SHININESS);
	ft_color_light_dist(specular, light, hit[1], scene);
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

void	ft_cy_normal(const t_obj *obj, const t_vec hit_point, t_vec normal)
{
	t_vec	axis;
	t_vec	cp;
	t_vec proj;
	double	dot;
	double	height;

	ft_cpy_vec(axis, obj->params + 3);
	ft_vec_norm(axis, axis);
	ft_vec_sub(cp, hit_point, obj->params);
	height = obj->params[6];
	dot = ft_vec_dot(cp, axis);
	if (fabs(dot) < 1e-4)
	{
		ft_vec_scale(normal, axis, -1);
		return;
	}
	if (fabs(dot - height) < 1e-4)
	{
		ft_cpy_vec(normal, axis);
		return;
	}
	ft_vec_scale(proj, axis, dot);
	ft_vec_sub(normal, cp, proj);
	ft_vec_norm(normal, normal);
}

void	ft_cone_normal(const t_obj *obj, const t_vec hit_point, t_vec normal)
{
	t_vec	cp;
	t_vec	proj;
	t_vec	axis;
	double	dot;

	ft_vec_sub(cp, hit_point, obj->params);
	ft_cpy_vec(axis, obj->params + 3);
	ft_vec_norm(axis, axis);
	dot = ft_vec_dot(cp, axis);
	ft_vec_scale(proj, axis, dot);
	ft_vec_sub(normal, cp, proj);
	ft_vec_norm(normal, normal);
}

void	ft_obj_normal(const t_obj *obj, const t_vec hit_point,
	t_vec normal, const t_vec ray_dir)
{
	if (obj->hit == ft_hit_s)
	{
		ft_vec_sub(normal, hit_point, obj->params);
		ft_vec_norm(normal, normal);
	}
	else if (obj->hit == ft_hit_p)
	{
		ft_cpy_vec(normal, obj->params + 3);
		ft_vec_norm(normal, normal);
		if (ft_vec_dot(normal, ray_dir) < 0)
			ft_vec_scale(normal, normal, -1);
	}
	else if (obj->hit == ft_hit_c)
		ft_cy_normal(obj, hit_point, normal);
	else if (obj->hit == ft_hit_cone)
		ft_cone_normal(obj, hit_point, normal);
	else
		ft_new_vec(normal, 0, 1, 0);
}

static void	ft_color_ads(t_color edit, const t_scene *scene, const t_obj *hit)
{
	t_color_ads	ads;
	t_ray		tmp;
	t_ray		cat[2];
	t_light		*light;
	t_vec		normal;

	ft_memset(&ads, 0, sizeof(t_color_ads));
	ft_color_mult(ads.ambient, hit->color, scene->ambient_light.color);
	ft_color_scale(ads.ambient, scene->ambient_light.ratio);
	light = scene->lights;
	while (light)
	{
		ft_new_ray(tmp, scene->ray[0], light->pos);
		ft_color_light_dist(ads.diffuse[1], light, tmp, scene);
		ft_color_mult(ads.diffuse[1], ads.diffuse[1], hit->color);
		ft_obj_normal(hit, scene->ray[0], normal, scene->ray[1]);
		ft_color_scale(ads.diffuse[1],
			fmax(0, ft_vec_dot(normal, tmp[1])));
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
	ft_color_ads(color, scene, hit);
	scene->mult = rules->ref_str;
	iter = -1;
	while (++iter < rules->ref)
	{
		hit = ft_hit_nearest_obj(hit_ray, scene->objects);
		if (!hit)
			break ;
		ft_memset(bounce, 0, 3);
		ft_color_ads(bounce, scene, hit);
		ft_color_reflect(reflect, bounce, scene->mult);
		ft_color_add(color, reflect);
		scene->mult *= .5f;
	}
	ft_color_fix(color);
	return (ft_convert_color(color));
}
