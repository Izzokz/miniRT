/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:54:09 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/27 11:01:59 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_free_obj(t_obj *head)
{
	t_obj	*tmp;

	while (head)
	{
		free((double *)head->params);
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

char	ft_hit_p(const t_obj *plane, t_ray ray)
{
	t_vec	tmp[2];
	double	dot;
	double	t;

	dot = ft_vec_dot(*(ray + 1), plane->params + 3);
	if (fabs(dot) < 1e-6)
		return (0);
	ft_vec_sub(*tmp, plane->params, *ray);
	t = ft_vec_dot(*tmp, plane->params + 3) / dot;
	if (t < 1e-6)
		return (0);
	ft_vec_scale(*tmp, *(ray + 1), t);
	ft_vec_add(*tmp, *ray, *tmp);
	if (ft_vec_dot(*(ray + 1), plane->params + 3) > 0)
		ft_vec_scale(*(tmp + 1), plane->params + 3, -1.0);
	else
		ft_cpy_vec(*(tmp + 1), plane->params + 3);
	ft_reflect(ray, tmp);
	return (1);
}
