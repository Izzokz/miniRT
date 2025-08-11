/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:37:22 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/05 13:54:08 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_reflect(t_ray ray, t_vec posnorm[2])
{
	double	dot;
	t_vec	tmp;

	ft_vec_scale(tmp, ray[1], 1e-3);
	ft_vec_add(ray[0], ray[0], tmp);
	dot = 2.0 * ft_vec_dot(ray[1], posnorm[1]);
	ft_vec_scale(tmp, posnorm[1], dot);
	ft_cpy_vec(ray[0], posnorm[0]);
	ft_vec_sub(ray[1], ray[1], tmp);
	ft_vec_norm(ray[1], ray[1]);
}

char	ft_hit_s(const t_obj *sphere, t_ray ray)
{
	double	abdt[4];
	t_vec	tmp[2];

	ft_vec_sub(tmp[0], ray[0], sphere->params);
	abdt[0] = ft_vec_dot(ray[1], ray[1]);
	abdt[1] = 2.0 * ft_vec_dot(tmp[0], ray[1]);
	abdt[2] = (abdt[1] * abdt[1])
		- (4.0 * abdt[0] * (ft_vec_dot(tmp[0], tmp[0])
				- ((*(sphere->params + 3) / 2) * (*(sphere->params + 3) / 2))));
	if (abdt[2] < 1e-6)
		return (0);
	abdt[3] = (-abdt[1] - sqrt(abdt[2])) / (2.0 * abdt[0]);
	if (abdt[3] < 1e-6)
		abdt[3] = (-abdt[1] + sqrt(abdt[2])) / (2.0 * abdt[0]);
	if (abdt[3] < 1e-6)
		return (0);
	ft_vec_scale(tmp[0], ray[1], abdt[3]);
	ft_vec_add(tmp[0], ray[0], tmp[0]);
	ft_vec_sub(tmp[1], tmp[0], sphere->params);
	ft_vec_norm(tmp[1], tmp[1]);
	ft_reflect(ray, tmp);
	return (1);
}
