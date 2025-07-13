/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_key_hook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:41:45 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/06 23:37:57 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline void	ft_set_rules_max(t_rules *rules)
{
	rules->ref = 4;
	rules->ref_str = .75;
	rules->pixel_cross = 1;
	rules->coloration = ft_blend_color;
}

static inline void	ft_move2(const char x, const char y,
	const char z, t_scene *scene)
{
	t_vec	move;
	t_vec	tmp;
	t_vec	delta;

	ft_new_vec(move, x, y, z);
	ft_vec_scale(delta, (t_vec){*scene->camera.orientation, 0, 0}, x);
	ft_vec_scale(tmp, g_up, y);
	ft_vec_add(delta, delta, tmp);
	ft_vec_scale(tmp, (t_vec){0, 0, *(scene->camera.orientation + 2)}, z);
	ft_vec_add(delta, delta, tmp);
	ft_vec_norm(delta, delta);
	ft_vec_scale(delta, delta, MOVE_SPEED);
	ft_vec_add(scene->camera.pos, scene->camera.pos, delta);
}

static inline char	ft_move(unsigned char keys, t_scene *scene)
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
	printf("cam:pos{%f, %f, %f}\n", scene->camera.pos[0], scene->camera.pos[1], scene->camera.pos[2]);
	return (1);
}

static inline void	ft_rotate_vec(t_vec v, const t_vec axis, const float angle)
{
	t_vec	tmp;
	t_vec	tmp2;
	float	cos_a;
	float	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	ft_vec_scale(tmp, v, cos_a);
	ft_vec_cross(tmp2, axis, v);
	ft_vec_scale(tmp2, tmp2, sin_a);
	ft_vec_add(v, tmp, tmp2);
	ft_vec_scale(tmp, axis, ft_vec_dot(axis, v) * (1 - cos_a));
	ft_vec_add(v, v, tmp);
}

static inline char	ft_rotate(const t_keys keys, t_scene *scene)
{
	float	yaw;
	float	pitch;
	t_vec	right;

	yaw = ((keys.right > 0) - (keys.left > 0)) * ROT_SPEED;
	pitch = ((keys.down > 0) - (keys.up > 0)) * ROT_SPEED;
	if (yaw == 0 && pitch == 0)
		return (0);
	scene->camera.gli.unlock(scene->camera.orientation,
		(char *)&scene->camera.gli);
	if (yaw != 0)
		ft_rotate_vec(scene->camera.orientation, scene->_up, yaw);
	if (pitch != 0)
	{
		ft_vec_cross(right, scene->_up, scene->camera.orientation);
		ft_vec_norm(right, right);
		ft_rotate_vec(scene->camera.orientation, right, pitch);
	}
	ft_vec_norm(scene->camera.orientation, scene->camera.orientation);
	scene->camera.gli.realign(scene->camera.orientation,
		(char *)&scene->camera.gli);
	ft_cpy_vec(scene->_forward, scene->camera.orientation);
	ft_vec_cross(scene->_right, g_up, scene->_forward);
	ft_vec_norm(scene->_right, scene->_right);
	ft_vec_cross(scene->_up, scene->_forward, scene->_right);
	ft_vec_norm(scene->_up, scene->_up);
	return (1);
}

void	ft_mlx_key_hook(const t_keys keys, t_scene *scene, t_mlx_obj *mobj)
{
	static t_rules	rules;
	static char		init = 0;

	if (!init)
	{
		++init;
		ft_set_rules_max(&rules);
		ft_mlx_img_update(mobj, scene, &rules);
		return ;
	}
	if (ft_move(*(unsigned char *)&keys, scene) + ft_rotate(keys, scene))
	{
		rules.pixel_cross = MRT_CROSS_PIXEL_PERF;
		rules.coloration = ft_color_mini;
		ft_mlx_img_update(mobj, scene, &rules);
	}
	else if (keys.r)
	{
		ft_set_rules_max(&rules);
		ft_mlx_img_update(mobj, scene, &rules);
	}
}
