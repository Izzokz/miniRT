/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_key_hook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:41:45 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/31 15:59:11 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline void	ft_set_rules_max(t_rules *rules, t_rules *max)
{
	rules->ref = max->ref;
	rules->ref_str = max->ref_str;
	rules->pixel_cross = 1;
	rules->coloration = max->coloration;
}

static inline void	ft_init_rules(t_rules *rules)
{
	rules->ref = MRT_MAX_REF;
	rules->ref_str = MRT_MAX_REF_STR;
	rules->pixel_cross = 1;
	rules->coloration = MRT_BEST_COLORATION;
}

static inline void	ft_set_rules_min(t_mlx_obj *mobj, t_rules *rules)
{
	if (rules->coloration != ft_color_mini)
	{
		ft_memset(mobj->img_data, 0, mobj->size_line * HEIGHT);
		rules->pixel_cross = MRT_PIXEL_CROSS_PERF;
		rules->coloration = ft_color_mini;
	}
}

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
	return (1);
}

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

static inline void	ft_apply_rotation(t_scene *scene)
{
	t_vec	right_rot;
	t_vec	up_rot;
	double	pitch_limit;

	pitch_limit = M_PI_2 - 0.15;
	ft_limit_pitch(scene, pitch_limit);
	ft_new_vec(scene->_up, 0, 1, 0);
	ft_calc_forward(scene);
	ft_calc_right_up(scene);
	ft_apply_roll(scene, right_rot, up_rot);
	ft_cpy_vec(scene->camera.orientation, scene->_forward);
}

static inline char ft_rotate_yaw(const t_keys keys, t_scene *scene)
{
	if (keys.left)
	{
		scene->_yaw += ROT_SPEED;
		return (1);
	}
	else if (keys.right)
	{
		scene->_yaw -= ROT_SPEED;
		return (1);
	}
	return (0);
}


static inline char ft_rotate_pitch(const t_keys keys, t_scene *scene)
{
	if (keys.up)
	{
		scene->_pitch += ROT_SPEED;
		return (1);
	}
	else if (keys.down)
	{
		scene->_pitch -= ROT_SPEED;
		return (1);
	}
	return (0);
}

static inline char ft_rotate_roll(const t_keys keys, t_scene *scene)
{
	if (keys.q)
	{
		scene->_roll += ROT_SPEED;
		return (1);
	}
	else if (keys.e)
	{
		scene->_roll -= ROT_SPEED;
		return (1);
	}
	return (0);
}

static inline char	ft_rotate(const t_keys keys, t_scene *scene)
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

static inline void	ft_reset_cam(t_scene *scene)
{
	const t_camera	*save;

	save = ft_get_const_cam();
	ft_memcpy(scene->camera.pos, save->pos, sizeof(t_vec));
	ft_memcpy(scene->camera.orientation, save->orientation, sizeof(t_vec));
	scene->camera.fov = save->fov;
	ft_new_vec(scene->_up, 0, 1, 0);
	ft_cpy_vec(scene->_forward, scene->camera.orientation);
	ft_vec_cross(scene->_right, scene->_forward, scene->_up);
	scene->_pitch = asin(*(scene->camera.orientation + 1));
	scene->_yaw = atan2(scene->_forward[2], scene->_forward[0]);
	scene->_roll = 0;
}

static inline void	ft_mlx_key_hook_r(t_mlx_obj *mobj, t_scene *scene,
	const t_keys keys, t_rules rules[3])
{
	if (keys.reset)
	{
		ft_set_rules_max(rules + 1, rules + 2);
		ft_set_rules_max(rules, rules + 1);
		ft_reset_cam(scene);
		ft_mlx_img_update(mobj, scene, rules, 1);
		return ;
	}
	if (keys.ctrl)
		ft_reset_cam(scene);
	if (!keys.ctrl || keys.shift)
		ft_set_rules_max(rules, rules + 1);
	else
		ft_set_rules_min(mobj, rules);
	ft_mlx_img_update(mobj, scene, rules, 1);
}

static inline void	ft_mlx_key_hook_c(t_mlx_obj *mobj, t_scene *scene,
	char ctrl, t_rules rules[2])
{
	char	*str;

	if (ctrl)
	{
		(rules + 1)->coloration = MRT_BEST_COLORATION;
		ft_set_rules_max(rules, rules + 1);
		ft_mlx_img_update(mobj, scene, rules, 1);
		return ;
	}
	ft_putstr_fd("\nChange Coloration:\n", 1);
	str = get_next_line(0);
	if (!str && write(1, "^D\n", 3))
		return ;
	if (ft_sequals(str, "reset\n"))
		(rules + 1)->coloration = MRT_BEST_COLORATION;
	else if (ft_sequals(str, "glass\n"))
		(rules + 1)->coloration = ft_color_glass;
	else if (ft_sequals(str, "blend\n"))
		(rules + 1)->coloration = ft_blend_color;
	else if (ft_sequals(str, "unicorn\n"))
		(rules + 1)->coloration = ft_unicorn;
	else if (ft_sequals(str, "virus\n"))
		(rules + 1)->coloration = ft_color_virus;
	else if (ft_sequals(str, "chill\n"))
		(rules + 1)->coloration = ft_color_chill;
	else if (ft_sequals(str, "error\n"))
		(rules + 1)->coloration = ft_color_error;
	else
		return (free(str));
	free(str);
	ft_set_rules_max(rules, rules + 1);
	ft_mlx_img_update(mobj, scene, rules, 1);
}

static void	ft_handle_actions(t_mlx_obj *mobj, t_scene *scene,
	t_keys *keys, t_rules rules[3])
{
	int	rerender;

	rerender = 0;
	if (keys->t)
		ft_open_editor(mobj, scene, rules);
	else if (keys->z && !keys->z_triggd)
	{
		rules->zoom = !rules->zoom;
		keys->z_triggd = 1;
		rerender = 1;
	}
	else if (!keys->ctrl && (ft_move(*(unsigned char *)keys, scene)
		| ft_rotate(*keys, scene)))
	{
		ft_set_rules_min(mobj, rules);
		rerender = 1;
	}
	else if (keys->r)
		ft_mlx_key_hook_r(mobj, scene, *keys, rules);
	else if (keys->c)
		ft_mlx_key_hook_c(mobj, scene, keys->ctrl, rules);
	if (rerender)
		ft_mlx_img_update(mobj, scene, rules, 1);
}

/*
*rules = actual
*(rules + 1) = custom maxed
*(rules + 2) = origin maxed
*/
inline void	ft_mlx_key_hook(t_mlx_obj *mobj, t_scene *scene, t_keys *keys)
{
	static t_rules	rules[3] = {0};
	static char		init = 0;

	if (!init)
	{
		ft_init_rules(rules + ++init + 1);
		ft_set_rules_max(rules + 1, rules + 2);
		ft_set_rules_max(rules, rules + 1);
		ft_mlx_img_update(mobj, scene, rules, 1);
		return ;
	}
	ft_menu_handler(keys, rules);
	ft_handle_actions(mobj, scene, keys, rules);
	ft_mlx_img_update(mobj, scene, rules, 0);
}
