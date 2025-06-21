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

char	ft_make_p(const t_vec posnorm[2], const t_color color)
{
	t_obj	*newobj;
	t_vec	normal;

	newobj = ft_get_uninit_obj();
	newobj->params = malloc(sizeof(double) * 6);
	if (!newobj->params)
		return (-1);
	ft_cpy_vec(normal, *(posnorm + 1));
	ft_vec_norm(normal, normal);
	ft_memcpy((void *)newobj->params,
		(double [6]){**posnorm, *(*posnorm + 1), *(*posnorm + 2),
		*normal, *(normal + 1), *(normal + 2)}, sizeof(double) * 6);
	newobj->type = 'p';
	ft_memcpy(newobj->color, color, 3);
	newobj->hit = ft_hit_p;
	return (0);
}

/* Tries to free objects even if they're not set so DON'T use if they're not */
void	ft_free_obj(void)
{
	t_obj	*all;
	int		i;

	all = ft_get_obj();
	i = -1;
	while ((*(all + ++i)).params)
		free((double *)(*(all + i)).params);
	free(all);
}

char	ft_hit_p(const t_obj plane, t_ray ray)
{
	t_vec	tmp[2];
	double	dot;
	double	t;

	ft_cpy_vec(*(tmp + 1), (t_vec){(*(plane.params + 3)), *(plane.params + 4),
		*(plane.params + 5)});
	dot = ft_vec_dot(*(ray + 1), *(tmp + 1));
	if (fabs(dot) < 0.0000001)
		return (0);
	ft_cpy_vec(*tmp, (t_vec){(*(plane.params)), *(plane.params + 1),
		*(plane.params + 2)});
	ft_vec_sub(*tmp, *tmp, *ray);
	t = ft_vec_dot(*tmp, *(tmp + 1)) / dot;
	if (t < 0.0)
		return (0);
	ft_vec_scale(*tmp, *(ray + 1), t);
	ft_vec_add(*tmp, *ray, *tmp);
	ft_reflect(ray, tmp);
	return (1);
}
