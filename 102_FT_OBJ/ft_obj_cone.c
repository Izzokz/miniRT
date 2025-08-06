/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:18:10 by lumugot           #+#    #+#             */
/*   Updated: 2025/08/05 14:13:05 by lumugot          ###   ########.fr       */
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

static double	intersect_base(const t_obj *co, t_ray ray, t_vec axis)
{
	t_vec	base_center;
	t_vec	p_to_base;
	t_vec	hit_point;
	double	t;
	double	dot_ray_axis;

	ft_vec_scale(base_center, axis, co->params[7]);
	ft_vec_add(base_center, co->params, base_center);
	dot_ray_axis = ft_vec_dot(*(ray + 1), axis);
	if (fabs(dot_ray_axis) < 1e-6)
		return (-1.0);
	ft_vec_sub(p_to_base, base_center, *ray);
	t = ft_vec_dot(p_to_base, axis) / dot_ray_axis;
	if (t < 1e-6)
		return (-1.0);
	ft_vec_scale(hit_point, ray[1], t);
	ft_vec_add(hit_point, ray[0], hit_point);
	ft_vec_sub(p_to_base, hit_point, base_center);
	if (ft_vec_dot(p_to_base, p_to_base) < pow(co->params[6] / 2.0, 2))
		return (t);
	return (-1.0);
}

static double	intersect_body(const t_obj *co, t_ray ray, t_vec axis)
{
	t_vec	oc;
	double	coeffs[3];
	double	dots[2];
	double	k;
	double	t;

	k = pow(co->params[6] / 2.0, 2) / pow(co->params[7], 2);
	ft_vec_sub(oc, ray[0], co->params);
	dots[0] = ft_vec_dot(ray[1], axis);
	dots[1] = ft_vec_dot(oc, axis);
	coeffs[0] = ft_vec_dot(*(ray + 1), *(ray + 1)) - (1 + k) * pow(dots[0], 2);
	coeffs[1] = 2 * (ft_vec_dot(*(ray + 1), oc) - (1 + k) * dots[0] * dots[1]);
	coeffs[2] = ft_vec_dot(oc, oc) - (1 + k) * pow(dots[1], 2);
	t = solve_quadratic(coeffs[0], coeffs[1], coeffs[2]);
	if (t < 0.0)
		return (-1.0);
	if (dots[1] + t * dots[0] >= 0 && dots[1] + t * dots[0] <= co->params[7])
		return (t);
	return (-1.0);
}

static void	get_normal(t_vec normal, const t_obj *co, t_vec hit, t_vec axis)
{
	t_vec	tmp;
	double	m;

	ft_vec_sub(tmp, hit, co->params);
	m = ft_vec_dot(tmp, axis);
	ft_vec_scale(normal, axis, m * (1 + pow(co->params[6] / 2.0, 2)
		/ pow(co->params[7], 2)));
	ft_vec_sub(normal, tmp, normal);
	ft_vec_norm(normal, normal);
}

char	ft_hit_cone(const t_obj *cone, t_ray ray)
{
	double	t_val[3];
	t_vec	hit_point;
	t_vec	normal;
	t_vec	axis;
	t_vec	posnorm[2];

	ft_cpy_vec(axis, cone->params + 3);
	ft_vec_norm(axis, axis);
	t_val[0] = intersect_body(cone, ray, axis);
	t_val[1] = intersect_base(cone, ray, axis);
	if (t_val[0] < 0 && t_val[1] < 0)
		return (0);
	if (t_val[0] > 0 && (t_val[1] < 0 || t_val[0] < t_val[1]))
		t_val[2] = t_val[0];
	else
		t_val[2] = t_val[1];
	ft_vec_scale(hit_point, *(ray + 1), t_val[2]);
	ft_vec_add(hit_point, *ray, hit_point);
	if (t_val[2] == t_val[0])
		get_normal(normal, cone, hit_point, axis);
	else
		ft_cpy_vec(normal, axis);
	ft_cpy_vec(posnorm[0], hit_point);
	ft_cpy_vec(posnorm[1], normal);
	ft_reflect(ray, posnorm);
	return (1);
}
