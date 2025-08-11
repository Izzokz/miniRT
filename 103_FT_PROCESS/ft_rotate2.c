/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:35:25 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/11 15:35:26 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	ft_limit_pitch(t_scene *scene, double pitch_limit)
{
	if (scene->_pitch > pitch_limit)
		scene->_pitch = pitch_limit;
	if (scene->_pitch < -pitch_limit)
		scene->_pitch = -pitch_limit;
}

static void	ft_calc_forward(t_scene *scene)
{
	scene->_forward[0] = cos(scene->_pitch) * cos(scene->_yaw);
	scene->_forward[1] = sin(scene->_pitch);
	scene->_forward[2] = cos(scene->_pitch) * sin(scene->_yaw);
	ft_vec_norm(scene->_forward, scene->_forward);
}

static void	ft_calc_right_up(t_scene *scene)
{
	ft_vec_cross(scene->_right, scene->_forward, scene->_up);
	ft_vec_norm(scene->_right, scene->_right);
}

static void	ft_apply_roll(t_scene *scene, t_vec right_rot, t_vec up_rot)
{
	double	cr;
	double	sr;
	double	roll;

	roll = scene->_roll;
	cr = cos(roll);
	sr = sin(roll);
	right_rot[0] = cr * scene->_right[0] - sr * scene->_up[0];
	right_rot[1] = cr * scene->_right[1] - sr * scene->_up[1];
	right_rot[2] = cr * scene->_right[2] - sr * scene->_up[2];
	up_rot[0] = sr * scene->_right[0] + cr * scene->_up[0];
	up_rot[1] = sr * scene->_right[1] + cr * scene->_up[1];
	up_rot[2] = sr * scene->_right[2] + cr * scene->_up[2];
	ft_cpy_vec(scene->_right, right_rot);
	ft_cpy_vec(scene->_up, up_rot);
	ft_vec_norm(scene->_right, scene->_right);
	ft_vec_norm(scene->_up, scene->_up);
}

inline void	ft_apply_rotation(t_scene *scene)
{
	t_vec	right_rot;
	t_vec	up_rot;
	double	pitch_limit;

	pitch_limit = (PI / 2) - 0.15;
	ft_limit_pitch(scene, pitch_limit);
	ft_new_vec(scene->_up, 0, 1, 0);
	ft_calc_forward(scene);
	ft_calc_right_up(scene);
	ft_apply_roll(scene, right_rot, up_rot);
	ft_cpy_vec(scene->camera.orientation, scene->_forward);
}
