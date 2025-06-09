/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:51:55 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/05/29 16:51:55 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_obj.h"

char	ft_make_c(const t_vec posnorm[2], const double dia,
	const double height, const t_color color)
{
	t_obj	*newobj;

	newobj = ft_get_uninit_obj();
	newobj->params = malloc(sizeof(double) * 8);
	if (!newobj->params)
		return (-1);
	ft_memcpy((void *)newobj->params,
		(double [8]){**posnorm, *(*posnorm + 1), *(*posnorm + 2),
		**(posnorm + 1), *(*(posnorm + 1) + 1), *(*(posnorm + 1) + 2),
		dia, height},
		sizeof(double) * 8);
	newobj->type = 'c';
	ft_memcpy(newobj->color, color, 3);
	newobj->hit = ft_hit_c;
	return (0);
}

char	ft_hit_c(const t_obj cylinder, t_ray ray)
{
	(void) cylinder;
	(void) ray;
	return (0);
}
