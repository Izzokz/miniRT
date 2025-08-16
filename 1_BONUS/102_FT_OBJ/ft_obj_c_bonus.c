/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_c_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:51:55 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/12 11:13:48 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static void	get_axis(const t_obj *cy, t_vec axis)
{
	ft_cpy_vec(axis, cy->params + 3);
	ft_vec_norm(axis, axis);
}

static double	intersect_body(const t_obj *cy, t_ray ray, t_vec axis)
{
	double	inside;
	double	outside;

	if (is_inside_cylinder(cy, ray[0], axis))
	{
		inside = intersect_body_inside(cy, ray, axis);
		return (inside);
	}
	else
	{
		outside = intersect_body_outside(cy, ray, axis);
		return (outside);
	}
}

static void	get_normal(t_vec normal, const t_obj *cy, t_ray ray, t_vec hit)
{
	t_vec	axis;
	t_vec	tmp;
	double	m;

	get_axis(cy, axis);
	ft_vec_sub(tmp, hit, cy->params);
	m = ft_vec_dot(tmp, axis);
	if (fabs(m) < EPSILON)
	{
		ft_cpy_vec(normal, axis);
		ft_vec_scale(normal, normal, -1.0);
	}
	else if (fabs(m - cy->params[7]) < EPSILON)
		ft_cpy_vec(normal, axis);
	else
	{
		ft_vec_scale(normal, axis, m);
		ft_vec_add(normal, cy->params, normal);
		ft_vec_sub(normal, hit, normal);
	}
	if (ft_vec_dot(ray[1], normal) > 0)
		ft_vec_scale(normal, normal, -1.0);
	ft_vec_norm(normal, normal);
}

char	ft_hit_c(const t_obj *cylinder, t_ray ray)
{
	double	val[3];
	t_vec	hit_point;
	t_vec	normal;
	t_vec	axis;
	t_vec	posnorm[2];

	get_axis(cylinder, axis);
	val[0] = intersect_body(cylinder, ray, axis);
	val[1] = intersect_caps(cylinder, ray, axis);
	if (val[0] < 0 && val[1] < 0)
		return (0);
	if (val[0] > 0 && (val[1] < 0 || val[0] < val[1]))
		val[2] = val[0];
	else
		val[2] = val[1];
	ft_vec_scale(hit_point, ray[1], val[2]);
	ft_vec_add(hit_point, ray[0], hit_point);
	get_normal(normal, cylinder, ray, hit_point);
	ft_cpy_vec(posnorm[0], hit_point);
	ft_cpy_vec(posnorm[1], normal);
	ft_reflect(ray, posnorm);
	return (1);
}
