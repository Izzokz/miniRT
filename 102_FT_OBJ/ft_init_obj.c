/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:36:33 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/06/05 14:36:34 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_obj.h"

static t_obj	*ft_obj(const t_obj *all)
{
	static t_obj	*save;

	if (all)
		save = all;
	return (save);
}

static inline void	ft_set_obj(const t_obj *all)
{
	ft_obj(all);
}

inline t_obj	*ft_get_obj(void)
{
	return (ft_obj(NULL));
}

/* Returns the first uninitialized object. */
t_obj	*ft_get_uninit_obj(void)
{
	t_obj	*all;
	int		i;

	all = ft_get_obj();
	i = -1;
	while (*(all + ++i).params)
		;
	return (all + i);
}

/*
Initialize objects and sets them.
Returns 0 on success, -1 on failure.
*/
char	ft_init_obj(const int i)
{
	t_obj	*newall;

	newall = malloc(sizeof(t_obj) * (i + 1));
	if (!newall)
		return (-1);
	*(newall + i) = '\0';
	while (--i >= 0)
		*(newall + i) = (t_obj){.params = NULL};
	ft_set_obj(newall);
	return (0);
}
