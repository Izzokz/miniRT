/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:51:55 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/31 15:05:03 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

static double	solve_quadratic(double a, double b, double c)
{
	double	discriminant;
	double	t1;
	double	t2;

	discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0)
		return (-1.0);
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t1 > 1e-6 && (t2 < 1e-6 || t1 < t2))
		return (t1);
	if (t2 > 1e-6)
		return (t2);
	return (-1.0);
}

static double	cap_intersection(const t_obj *cy, t_ray ray, t_vec axis, int upper)
{
	t_vec	center;
	t_vec	tmp1;
	t_vec	tmp2;
	double	t;
	double	dot_ray_axis;

	if (upper)
	{
		ft_vec_scale(center, axis, cy->params[7]);
		ft_vec_add(center, cy->params, center);
	}
	else
		ft_cpy_vec(center, cy->params);
	dot_ray_axis = ft_vec_dot(*(ray + 1), axis);
	if (fabs(dot_ray_axis) < 1e-6)
		return (-1.0);
	ft_vec_sub(tmp1, center, *ray);
	t = ft_vec_dot(tmp1, axis) / dot_ray_axis;
	ft_vec_scale(tmp2, ray[1], t);
	ft_vec_add(tmp2, *ray, tmp2);
	ft_vec_sub(tmp1, tmp2, center);
	if (!(t > 1e-6 && ft_vec_dot(tmp1, tmp1) < pow(cy->params[6] / 2.0, 2)))
		return (-1.0);
	return (t);
}

static double	intersect_caps(const t_obj *cy, t_ray ray, t_vec axis)
{
	double	t[2];

	t[0] = cap_intersection(cy, ray, axis, 0);
	t[1] = cap_intersection(cy, ray, axis, 1);
	if (t[0] > 0 && (t[1] < 0 || t[0] < t[1]))
		return (t[0]);
	if (t[1] > 0)
		return (t[1]);
	return (-1.0);
}

static double	intersect_body(const t_obj *cy, t_ray ray, t_vec axis)
{
	t_vec	oc;
	double	coeffs[3];
	double	dots[2];
	double	t;
	double	m;

	ft_vec_sub(oc, *ray, cy->params);
	dots[0] = ft_vec_dot(ray[1], axis);
	dots[1] = ft_vec_dot(oc, axis);
	coeffs[0] = ft_vec_dot(ray[1], ray[1]) - dots[0] * dots[0];
	coeffs[1] = 2.0 * (ft_vec_dot(ray[1], oc) - dots[0] * dots[1]);
	coeffs[2] = ft_vec_dot(oc, oc) - dots[1] * dots[1]
		- pow(cy->params[6] / 2.0, 2);
	t = solve_quadratic(coeffs[0], coeffs[1], coeffs[2]);
	if (t < 0.0)
		return (-1.0);
	m = dots[1] + t * dots[0];
	if (m >= 0 && m <= cy->params[7])
		return (t);
	return (-1.0);
}

static void	get_normal(t_vec normal, const t_obj *cy, t_ray ray, t_vec hit)
{
	t_vec	axis;
	t_vec	tmp;
	double	m;

	ft_cpy_vec(axis, cy->params + 3);
	ft_vec_sub(tmp, hit, cy->params);
	m = ft_vec_dot(tmp, axis);
	if (fabs(m) < 1e-6)
	{
		ft_cpy_vec(normal, axis);
		ft_vec_scale(normal, normal, -1.0);
   	}
	else if (fabs(m - cy->params[7]) < 1e-6)
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
	double	t_val[3];
	t_vec	hit_point;
	t_vec	normal;
	t_vec	axis;
	t_vec	posnorm[2];

	ft_cpy_vec(axis, cylinder->params + 3);
	ft_vec_norm(axis, axis);
	t_val[0] = intersect_body(cylinder, ray, axis);
	t_val[1] = intersect_caps(cylinder, ray, axis);
	if (t_val[0] < 0 && t_val[1] < 0)
		return (0);
	if (t_val[0] > 0 && (t_val[1] < 0 || t_val[0] < t_val[1]))
		t_val[2] = t_val[0];
	else
		t_val[2] = t_val[1];
	ft_vec_scale(hit_point, ray[1], t_val[2]);
	ft_vec_add(hit_point, *ray, hit_point);
	get_normal(normal, cylinder, ray, hit_point);
	ft_cpy_vec(posnorm[0], hit_point);
	ft_cpy_vec(posnorm[1], normal);
	ft_reflect(ray, posnorm);
	return (1);
}
