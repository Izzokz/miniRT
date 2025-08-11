/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_key_hook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:41:45 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/09 21:41:32 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	set_speed(t_scene *scene, t_keys *keys)
{
	if (keys->p_up)
		scene->m_speed += 0.010;
	if (keys->p_down)
		scene->m_speed -= 0.010;
	if (scene->m_speed < 0.010)
		scene->m_speed = 0.010;
	if (scene->m_speed > 0.200)
		scene->m_speed = 0.200;
	if (keys->r_speed_up)
		scene->r_speed += 0.0010;
	if (keys->r_speed_down)
		scene->r_speed -= 0.0010;
	if (scene->r_speed < 0.0010)
		scene->r_speed = 0.0010;
	if (scene->r_speed > 0.0500)
		scene->r_speed = 0.0500;
}

static void	ft_handle_actions(t_mlx_obj *mobj, t_scene *scene,
	t_keys *keys, t_rules rules[3])
{
	int	rerender;

	rerender = 0;
	set_speed(scene, keys);
	if (keys->t)
		ft_open_editor(mobj, scene, rules);
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
rules[0] = actual
rules[1] = custom maxed
rules[2] = origin maxed
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
	ft_menu_handler(scene, mobj, keys, rules);
	ft_handle_actions(mobj, scene, keys, rules);
}
