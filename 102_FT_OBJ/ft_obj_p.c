/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:54:09 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/06/20 15:28:28 by kzhen-cl         ###   ########.fr       */
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

	ft_cpy_vec(*(tmp + 1), (t_vec){(*(plane->params + 3)), *(plane->params + 4),
		*(plane->params + 5)});
	dot = ft_vec_dot(*(ray + 1), *(tmp + 1));
	if (fabs(dot) < 0.0000001)
		return (0);
	ft_cpy_vec(*tmp, (t_vec){(*(plane->params)), *(plane->params + 1),
		*(plane->params + 2)});
	ft_vec_sub(*tmp, *tmp, *ray);
	t = ft_vec_dot(*tmp, *(tmp + 1)) / dot;
	if (t < 0.0)
		return (0);
	ft_vec_scale(*tmp, *(ray + 1), t);
	ft_vec_add(*tmp, *ray, *tmp);
	ft_reflect(ray, tmp);
	return (1);
}
