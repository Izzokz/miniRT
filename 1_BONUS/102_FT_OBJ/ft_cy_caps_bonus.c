/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cy_caps_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:36:21 by lumugot           #+#    #+#             */
/*   Updated: 2025/08/11 22:45:38 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT_bonus.h"

inline	double	cap_intersection(const t_obj *cy, t_ray ray, t_vec axis,
	int upper)
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
	dot_ray_axis = ft_vec_dot(ray[1], axis);
	if (fabs(dot_ray_axis) < EPSILON)
		return (-1.0);
	ft_vec_sub(tmp1, center, ray[0]);
	t = ft_vec_dot(tmp1, axis) / dot_ray_axis;
	ft_vec_scale(tmp2, ray[1], t);
	ft_vec_add(tmp2, ray[0], tmp2);
	ft_vec_sub(tmp1, tmp2, center);
	if (t > EPSILON && ft_vec_dot(tmp1, tmp1) < pow(cy->params[6] / 2.0, 2))
		return (t);
	return (-1.0);
}

inline	double	intersect_caps(const t_obj *cy, t_ray ray, t_vec axis)
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
