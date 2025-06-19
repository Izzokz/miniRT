/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:36:33 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/06/19 13:15:00 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

static t_obj	*ft_obj(const t_obj *all)
{
	static t_obj	*save;

	if (all)
		save = (t_obj *)all;
	return (save);
}

static inline void	ft_set_obj(const t_obj *all)
{
	ft_obj(all);
}

inline t_obj	*ft_get_obj(void)
{
	return (ft_obj((void *)0));
}

/* Returns the first uninitialized object. */
t_obj	*ft_get_uninit_obj(void)
{
	t_obj	*all;
	int		i;

	all = ft_get_obj();
	i = -1;
	while ((*(all + ++i)).params)
		;
	return (all + i);
}

/*
Initialize objects and sets them.
Returns 0 on success, -1 on failure.
*/
char	ft_init_obj(int i)
{
	t_obj	*newall;

	newall = malloc(sizeof(t_obj) * (i + 1));
	if (!newall)
		return (-1);
	while (--i + 1 >= 0)
		*(newall + i + 1) = (t_obj){.params = (void *)0};
	ft_set_obj(newall);
	return (0);
}
