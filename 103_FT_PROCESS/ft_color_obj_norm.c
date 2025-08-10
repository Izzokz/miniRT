/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_obj_norm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 15:23:22 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/10 15:23:25 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline void	ft_cy_normal(const t_obj *obj,
	const t_vec hit_point, t_vec normal)
{
	t_vec	axis;
	t_vec	cp;
	t_vec	proj;
	double	dot;
	double	height;

	ft_cpy_vec(axis, obj->params + 3);
	ft_vec_norm(axis, axis);
	ft_vec_sub(cp, hit_point, obj->params);
	height = obj->params[7];
	dot = ft_vec_dot(cp, axis);
	if (fabs(dot) < 1e-4)
	{
		ft_vec_scale(normal, axis, -1);
		return ;
	}
	if (fabs(dot - height) < 1e-4)
	{
		ft_cpy_vec(normal, axis);
		return ;
	}
	ft_vec_scale(proj, axis, dot);
	ft_vec_sub(normal, cp, proj);
	ft_vec_norm(normal, normal);
}

static inline void	ft_cone_normal(const t_obj *obj,
	const t_vec hit_point, t_vec normal)
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

inline void	ft_obj_normal(const t_obj *obj, const t_vec hit_point,
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
