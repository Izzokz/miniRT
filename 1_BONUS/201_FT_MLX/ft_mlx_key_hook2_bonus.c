/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_key_hook2_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:03:40 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/11 18:45:33 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

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

inline void	ft_mlx_key_hook_r(t_mlx_obj *mobj, t_scene *scene,
	const t_keys keys, t_rules rules[2])
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

static inline char	ft_color_set(const char *const str, t_rules rules[2])
{
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
		return (0);
	return (1);
}

inline void	ft_mlx_key_hook_c(t_mlx_obj *mobj, t_scene *scene,
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
	if (!ft_color_set(str, rules))
		return (free(str));
	free(str);
	ft_set_rules_max(rules, rules + 1);
	ft_mlx_img_update(mobj, scene, rules, 1);
}
