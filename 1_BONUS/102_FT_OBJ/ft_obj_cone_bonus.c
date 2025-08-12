/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_cone_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:18:10 by lumugot           #+#    #+#             */
/*   Updated: 2025/08/12 11:14:06 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

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

static	int	check_val(double t_val[3])
{
	if (t_val[0] < 0 && t_val[1] < 0)
		return (0);
	if (t_val[0] > 0 && (t_val[1] < 0 || t_val[0] < t_val[1]))
		t_val[2] = t_val[0];
	else
		t_val[2] = t_val[1];
	return (1);
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
	t_val[0] = intersect_body_cone(cone, ray, axis);
	t_val[1] = intersect_base_cone(cone, ray, axis);
	if (check_val(t_val) == 0)
		return (0);
	ft_vec_scale(hit_point, ray[1], t_val[2]);
	ft_vec_add(hit_point, ray[0], hit_point);
	if (t_val[2] == t_val[0])
		get_normal(normal, cone, hit_point, axis);
	else
		ft_cpy_vec(normal, axis);
	ft_cpy_vec(posnorm[0], hit_point);
	ft_cpy_vec(posnorm[1], normal);
	ft_reflect(ray, posnorm);
	return (1);
}
