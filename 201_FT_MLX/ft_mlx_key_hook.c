/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_key_hook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:41:45 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/17 17:08:44 by lumugot          ###   ########.fr       */
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

	ft_new_vec(delta, x, y, z);
	ft_vec_scale(delta, (t_vec){(*scene->camera.orientation), 0, 0}, x);
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
	return (1);
}

static inline void	ft_rotate_vec(t_vec v, const t_vec axis, const double angle)
{
	t_vec	tmp;
	double	c;
	double	s;
	double	dot;

	ft_cpy_vec(tmp, v);
	dot = ft_vec_dot(v, axis);
	c = cos(angle);
	s = sin(angle);
	*v = *tmp * c + (1 - c) * dot * *axis
		+ s * (*(axis + 1) * *(tmp + 2) - *(axis + 2) * *(tmp + 1));
	*(v + 1) = *(tmp + 1) * c + (1 - c) * dot * *(axis + 1)
		+ s * (*(axis + 2) * *tmp - *axis * *(tmp + 2));
	*(v + 2) = *(tmp + 2) * c + (1 - c) * dot * *(axis + 2)
		+ s * (*axis * *(tmp + 1) - *(axis + 1) * *tmp);
	ft_vec_norm(v, v);
}

static inline void	ft_clamp_rotation_pitch(double *actual, double *add)
{
	double	tmp;

	tmp = *actual + *add;
	if (tmp > 1.5533430342749532)
	{
		*add = 1.5533430342749532 - *actual;
		*actual = 1.5533430342749532;
	}
	else if (tmp < -1.5533430342749532)
	{
		*add = -1.5533430342749532 - *actual;
		*actual = -1.5533430342749532;
	}
	else
		*actual += *add;
}

static inline char	ft_rotate(const t_keys keys, t_scene *scene)
{
	double	yaw;
	double	pitch;

	yaw = (keys.right - keys.left) * ROT_SPEED;
	pitch = (keys.down - keys.up) * ROT_SPEED;
	if (yaw == 0 && pitch == 0)
		return (0);
	if (yaw)
	{
		ft_rotate_vec(scene->camera.orientation, g_up, yaw);
		ft_vec_cross(scene->_right, scene->camera.orientation, g_up);
		ft_vec_norm(scene->_right, scene->_right);
		ft_vec_cross(scene->_up, scene->_right, scene->camera.orientation);
		ft_vec_norm(scene->_up, scene->_up);
	}
	ft_clamp_rotation_pitch(&scene->_pitch, &pitch);
	if (pitch)
	{
		ft_rotate_vec(scene->camera.orientation, scene->_right, -pitch);
		ft_vec_cross(scene->_up, scene->_right, scene->camera.orientation);
		ft_vec_norm(scene->_up, scene->_up);
		ft_vec_cross(scene->_right, scene->camera.orientation, scene->_up);
		ft_vec_norm(scene->_right, scene->_right);
	}
	return (1);
}

static inline void	ft_reset_cam(t_scene *scene)
{
	const t_camera	*save;

	save = ft_get_const_cam();
	ft_memcpy(scene->camera.pos, save->pos, 3 * sizeof(double));
	ft_memcpy(scene->camera.orientation, save->orientation, 3 * sizeof(double));
	scene->camera.fov = save->fov;
	ft_new_vec(scene->_up, 0, 1, 0);
	ft_cpy_vec(scene->_forward, scene->camera.orientation);
	ft_vec_cross(scene->_right, scene->_forward, scene->_up);
	scene->_pitch = asin(*(scene->camera.orientation + 1));
}

static inline void	ft_mlx_key_hook_r(t_mlx_obj *mobj, t_scene *scene,
	const t_keys keys, t_rules rules[3])
{
	if (keys.reset)
	{
		ft_set_rules_max(rules + 1, rules + 2);
		ft_set_rules_max(rules, rules + 1);
		ft_reset_cam(scene);
		ft_mlx_img_update(mobj, scene, rules);
		return ;
	}
	if (keys.ctrl)
		ft_reset_cam(scene);
	if (!keys.ctrl || keys.shift)
		ft_set_rules_max(rules, rules + 1);
	else
		ft_set_rules_min(mobj, rules);
	ft_mlx_img_update(mobj, scene, rules);
}

static inline void	ft_mlx_key_hook_c(t_mlx_obj *mobj, t_scene *scene,
	char ctrl, t_rules rules[2])
{
	char	*str;

	if (ctrl)
	{
		(rules + 1)->coloration = MRT_BEST_COLORATION;
		ft_set_rules_max(rules, rules + 1);
		ft_mlx_img_update(mobj, scene, rules);
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
	ft_mlx_img_update(mobj, scene, rules);
}

/*
*rules = actual
*(rules + 1) = custom maxed
*(rules + 2) = origin maxed
*/
inline void	ft_mlx_key_hook(t_mlx_obj *mobj, t_scene *scene, t_keys *keys)
{
	static t_rules	rules[3] = (t_rules [3]){(t_rules){0}, (t_rules){0},
		(t_rules){0}};
	static char		init = 0;

	if (!init)
	{
		ft_init_rules(rules + ++init + 1);
		ft_set_rules_max(rules + 1, rules + 2);
		ft_set_rules_max(rules, rules + 1);
		ft_mlx_img_update(mobj, scene, rules);
		return ;
	}
	if (keys->z && !keys->z_triggd)
		ft_mlx_img_update(mobj + ++rules->zoom * ++keys->z, scene, rules);
	if (!keys->ctrl
		&& ft_move(*(unsigned char *)keys, scene) + ft_rotate(*keys, scene))
	{
		ft_set_rules_min(mobj, rules);
		ft_mlx_img_update(mobj, scene, rules);
	}
	else if (keys->r)
		ft_mlx_key_hook_r(mobj, scene, *keys, rules);
	else if (keys->c)
		ft_mlx_key_hook_c(mobj, scene, keys->ctrl, rules);
}
