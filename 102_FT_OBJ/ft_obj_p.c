/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:54:09 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/06 23:32:58 by lumugot          ###   ########.fr       */
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
	t_vec	tmp_scale;
	double	dot;
	double	t;

	dot = ft_vec_dot(*(ray + 1), plane->params + 3);
	if (fabs(dot) < 1e-6)
		return (0);
	ft_vec_sub(*tmp, *ray, plane->params);
	ft_vec_scale(tmp_scale, *tmp, 2);
	ft_vec_sub(*tmp, *tmp, tmp_scale);
	t = ft_vec_dot(*tmp, plane->params + 3) / dot;
	if (t < 0.0)
		return (0);
	ft_vec_scale(*tmp, *(ray + 1), t);
	ft_vec_add(*tmp, *ray, *tmp);
	ft_vec_sub(*(tmp + 1), *tmp, plane->params);
	ft_vec_norm(*(tmp + 1), *(tmp + 1));
	ft_reflect(ray, tmp);
	return (1);
}
