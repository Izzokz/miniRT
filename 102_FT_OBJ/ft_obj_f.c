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

char	ft_make_c(t_vec posnorm[2], t_color color)
{
	t_obj	*newobj;

	newobj = ft_get_uninit_obj();
	newobj->params = malloc(sizeof(double) * 6);
	if (!newobj->params)
		return (-1);
	ft_memcpy(newobj->params,
		(double [6]){**posnorm, *(*posnorm + 1), *(*posnorm + 2),
		**(posnorm + 1), *(*(posnorm + 1) + 1), *(*(posnorm + 1) + 2)},
		sizeof(double) * 6);
	newobj->type = 'f';
	ft_memcpy(newobj->color, color, 3);
	newobj->hit = ft_hit_f;
	return (0);
}

void	ft_free_obj(t_obj *all)
{
	int	i;

	i = -1;
	while (*(all + ++i))
		free(*(all + i).params);
	free(all);
}

char	ft_hit_f(const t_obj flat, t_ray ray)
{
	return (0);
}
