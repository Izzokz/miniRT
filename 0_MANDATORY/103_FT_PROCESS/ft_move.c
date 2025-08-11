/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:41:32 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/11 22:24:35 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline void	ft_move2(const char x, const char y,
	const char z, t_scene *scene)
{
	t_vec	delta;
	t_vec	tmp;

	ft_new_vec(delta, 0, 0, 0);
	if (x)
	{
		ft_vec_scale(tmp, scene->_right, -x);
		ft_vec_add(delta, delta, tmp);
	}
	if (y)
	{
		ft_vec_scale(tmp, scene->_up, y);
		ft_vec_add(delta, delta, tmp);
	}
	if (z)
	{
		ft_vec_scale(tmp, scene->camera.orientation, z);
		ft_vec_add(delta, delta, tmp);
	}
	ft_vec_scale(delta, delta, scene->m_speed);
	ft_vec_add(scene->camera.pos, scene->camera.pos, delta);
	ft_vec_norm(delta, delta);
}

inline char	ft_move(unsigned char keys, t_scene *scene)
{
	char	x;
	char	y;
	char	z;

	x = ((keys >> 1) & 1) - ((keys >> 0) & 1);
	y = ((keys >> 3) & 1) - ((keys >> 2) & 1);
	z = ((keys >> 5) & 1) - ((keys >> 4) & 1);
	if (!x && !y && !z)
		return (0);
	ft_move2(x, y, z, scene);
	return (1);
}
