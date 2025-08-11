/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cy_inside_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:37:29 by lumugot           #+#    #+#             */
/*   Updated: 2025/08/11 22:46:18 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT_bonus.h"

inline	int	is_inside_cylinder(const t_obj *cy, t_vec point, t_vec axis)
{
	t_vec	tmp;
	double	m;

	ft_vec_sub(tmp, point, cy->params);
	m = ft_vec_dot(tmp, axis);
	if (m < 0 || m > cy->params[7])
		return (0);
	if (ft_vec_dot(tmp, tmp) - m * m < pow(cy->params[6] / 2.0, 2))
		return (1);
	return (0);
}

inline	double	solve_cylinder_quadratic_inside(double a, double b, double c)
{
	double	discriminant;
	double	t1;
	double	t2;

	discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0)
		return (-1.0);
	t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t1 > 1e-6 && t2 > 1e-6)
	{
		if (t1 > t2)
			return (t1);
		else
			return (t2);
	}
	if (t1 > 1e-6)
		return (t1);
	if (t2 > 1e-6)
		return (t2);
	return (-1.0);
}

inline	double	intersect_body_inside(const t_obj *cy, t_ray ray, t_vec axis)
{
	t_vec	oc;
	double	coeffs[3];
	double	dots[2];
	double	t;
	double	m;

	ft_vec_sub(oc, ray[0], cy->params);
	dots[0] = ft_vec_dot(ray[1], axis);
	dots[1] = ft_vec_dot(oc, axis);
	coeffs[0] = ft_vec_dot(ray[1], ray[1]) - dots[0] * dots[0];
	coeffs[1] = 2.0 * (ft_vec_dot(ray[1], oc) - dots[0] * dots[1]);
	coeffs[2] = ft_vec_dot(oc, oc) - dots[1] * dots[1]
		- pow(cy->params[6] / 2.0, 2);
	t = solve_cylinder_quadratic_inside(coeffs[0], coeffs[1], coeffs[2]);
	if (t < 1e-6)
		return (-1.0);
	m = dots[1] + t * dots[0];
	if (m >= 0 && m <= cy->params[7])
		return (t);
	return (-1.0);
}
