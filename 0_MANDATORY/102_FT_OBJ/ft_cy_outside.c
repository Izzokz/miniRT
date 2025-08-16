/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cy_outside.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:26:06 by lumugot           #+#    #+#             */
/*   Updated: 2025/08/11 22:26:45 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

inline	double	solve_cylinder_quadratic_outside(double a, double b, double c)
{
	double	discriminant;
	double	t1;
	double	t2;

	discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0)
		return (-1.0);
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t1 > EPSILON && t2 > EPSILON)
	{
		if (t1 < t2)
			return (t1);
		else
			return (t2);
	}
	if (t1 > EPSILON)
		return (t1);
	if (t2 > EPSILON)
		return (t2);
	return (-1.0);
}

inline	double	intersect_body_outside(const t_obj *cy, t_ray ray, t_vec axis)
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
	t = solve_cylinder_quadratic_outside(coeffs[0], coeffs[1], coeffs[2]);
	if (t < EPSILON)
		return (-1.0);
	m = dots[1] + t * dots[0];
	if (m >= 0 && m <= cy->params[7])
		return (t);
	return (-1.0);
}
