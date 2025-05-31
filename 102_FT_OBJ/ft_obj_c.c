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

t_obj	*ft_make_c(t_vec posnorm[2], double dia_hei[2], unsigned char color[3])
{
	t_obj	*newobj;

	newobj = malloc(sizeof(t_obj));
	if (!newobj)
		return (NULL);
	newobj->params = malloc(sizeof(double) * 8);
	if (!newobj->params)
	{
		free(newobj);
		return (NULL);
	}
	ft_memcpy(newobj->params,
		(double [8]){**posnorm, *(*posnorm + 1), *(*posnorm + 2),
		**(posnorm + 1), *(*(posnorm + 1) + 1), *(*(posnorm + 1) + 2),
		*dia_hei, *(dia_hei + 1)},
		sizeof(double) * 8);
	newobj->type = 'c';
	ft_memcpy(newobj->color, color, 3);
	newobj->hit = ft_hit_c;
	return (newobj);
}

char	ft_hit_c(const t_obj cylinder, t_ray ray)
{
	return (0);
}
