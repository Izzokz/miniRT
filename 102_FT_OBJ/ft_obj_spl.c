/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_spl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:37:22 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/05/29 15:37:23 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_obj.h"

t_obj	*ft_make_spl(char type, t_vec pos, double attr, unsigned char color[3])
{
	t_obj	*newobj;

	newobj = malloc(sizeof(t_obj));
	if (!newobj)
		return (NULL);
	newobj->params = malloc(sizeof(double) * 4);
	if (!newobj->params)
	{
		free(newobj);
		return (NULL);
	}
	ft_memcpy(newobj->params, (double [4]){*pos, *(pos + 1), *(pos + 2), attr},
		sizeof(double) * 4);
	newobj->type = type;
	ft_memcpy(newobj->color, color, 3);
	newobj->hit = ft_hit_l;
	if (type == 's')
		newobj->hit = ft_hit_s;
	else if (type == 'p')
		newobj->hit = ft_hit_l;
	return (newobj);
}

char	ft_hit_s(const t_obj obj, t_ray ray)
{
	
}

char	ft_hit_p(const t_obj obj, t_ray ray)
{
	
}

char	ft_hit_l(const t_obj obj, t_ray ray)
{
	
}
