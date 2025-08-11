/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:26:07 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/11 22:25:19 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline char	ft_rotate_yaw(const t_keys keys, t_scene *scene)
{
	if (keys.left)
	{
		scene->_yaw += scene->r_speed;
		return (1);
	}
	else if (keys.right)
	{
		scene->_yaw -= scene->r_speed;
		return (1);
	}
	return (0);
}

static inline char	ft_rotate_pitch(const t_keys keys, t_scene *scene)
{
	if (keys.up)
	{
		scene->_pitch += scene->r_speed;
		return (1);
	}
	else if (keys.down)
	{
		scene->_pitch -= scene->r_speed;
		return (1);
	}
	return (0);
}

static inline char	ft_rotate_roll(const t_keys keys, t_scene *scene)
{
	if (keys.q)
	{
		scene->_roll += scene->r_speed;
		return (1);
	}
	else if (keys.e)
	{
		scene->_roll -= scene->r_speed;
		return (1);
	}
	return (0);
}

inline char	ft_rotate(const t_keys keys, t_scene *scene)
{
	char	rotated;

	rotated = 0;
	if (ft_rotate_yaw(keys, scene))
		rotated = 1;
	if (ft_rotate_pitch(keys, scene))
		rotated = 1;
	if (ft_rotate_roll(keys, scene))
		rotated = 1;
	if (rotated)
		ft_apply_rotation(scene);
	return (rotated);
}
