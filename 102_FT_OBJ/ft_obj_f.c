/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_f.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:54:09 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/05/29 16:54:10 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_obj.h"

t_obj	*ft_make_c(t_vec posnorm[2], unsigned char color[3])
{
	t_obj	*newobj;

	newobj = malloc(sizeof(t_obj));
	if (!newobj)
		return (NULL);
	newobj->params = malloc(sizeof(double) * 6);
	if (!newobj->params)
	{
		free(newobj);
		return (NULL);
	}
	ft_memcpy(newobj->params,
		(double [6]){**posnorm, *(*posnorm + 1), *(*posnorm + 2),
		**(posnorm + 1), *(*(posnorm + 1) + 1), *(*(posnorm + 1) + 2)},
		sizeof(double) * 6);
	newobj->type = 'f';
	ft_memcpy(newobj->color, color, 3);
	newobj->hit = ft_hit_f;
	return (newobj);
}

void	ft_free_obj(t_obj *obj)
{
	free(obj->params);
	free(obj);
}

char	ft_hit_f(const t_obj flat, t_ray ray)
{
	return (0);
}
