/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect_cone_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 09:56:20 by lumugot           #+#    #+#             */
/*   Updated: 2025/08/12 10:25:02 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT_bonus.h"

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
	if (t1 > EPSILON && (t2 < EPSILON || t1 < t2))
		return (t1);
	if (t2 > EPSILON)
		return (t2);
	return (-1.0);
}

inline	double	intersect_base_cone(const t_obj *co, t_ray ray, t_vec axis)
{
	t_vec	base_center;
	t_vec	p_to_base;
	t_vec	hit_point;
	double	t;
	double	dot_ray_axis;

	ft_vec_scale(base_center, axis, co->params[7]);
	ft_vec_add(base_center, co->params, base_center);
	dot_ray_axis = ft_vec_dot(ray[1], axis);
	if (fabs(dot_ray_axis) < EPSILON)
		return (-1.0);
	ft_vec_sub(p_to_base, base_center, ray[0]);
	t = ft_vec_dot(p_to_base, axis) / dot_ray_axis;
	if (t < EPSILON)
		return (-1.0);
	ft_vec_scale(hit_point, ray[1], t);
	ft_vec_add(hit_point, ray[0], hit_point);
	ft_vec_sub(p_to_base, hit_point, base_center);
	if (ft_vec_dot(p_to_base, p_to_base) < pow(co->params[6] / 2.0, 2))
		return (t);
	return (-1.0);
}

inline	double	intersect_body_cone(const t_obj *co, t_ray ray, t_vec axis)
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
	coeffs[0] = ft_vec_dot(ray[1], ray[1]) - (1 + k) * pow(dots[0], 2);
	coeffs[1] = 2 * (ft_vec_dot(ray[1], oc) - (1 + k) * dots[0] * dots[1]);
	coeffs[2] = ft_vec_dot(oc, oc) - (1 + k) * pow(dots[1], 2);
	t = solve_quadratic(coeffs[0], coeffs[1], coeffs[2]);
	if (t < 0.0)
		return (-1.0);
	if (dots[1] + t * dots[0] >= 0 && dots[1] + t * dots[0] <= co->params[7])
		return (t);
	return (-1.0);
}
