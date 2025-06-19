/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_f.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:54:09 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/06/19 13:15:01 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

char	ft_make_f(const t_vec posnorm[2], const t_color color)
{
	t_obj	*newobj;

	newobj = ft_get_uninit_obj();
	newobj->params = malloc(sizeof(double) * 6);
	if (!newobj->params)
		return (-1);
	ft_memcpy((void *)newobj->params,
		(double [6]){**posnorm, *(*posnorm + 1), *(*posnorm + 2),
		**(posnorm + 1), *(*(posnorm + 1) + 1), *(*(posnorm + 1) + 2)},
		sizeof(double) * 6);
	newobj->type = 'f';
	ft_memcpy(newobj->color, color, 3);
	newobj->hit = ft_hit_f;
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

char	ft_hit_f(const t_obj flat, t_ray ray)
{
	(void) flat;
	(void) ray;
	return (0);
}
