/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:03:12 by lumugot           #+#    #+#             */
/*   Updated: 2025/08/04 13:03:03 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

void	ft_display_menu(t_mlx_obj *mobj, t_rules *rules)
{
	if (rules->menu_state == 1)
		ft_display_main_help(mobj);
	else if (rules->menu_state == 2)
		ft_display_movement_help(mobj);
	else if (rules->menu_state == 3)
		ft_display_render_help(mobj);
	else if (rules->menu_state == 4)
		ft_display_object_help(mobj);
	else if (rules->menu_state == 0)
		mlx_string_put(mobj->mlx, mobj->win, 15, 20, 0xFFFFFF,
			"Press TAB to display the key menu");
}

static void	ft_menu_navigation(t_keys *keys, t_rules *rules)
{
	if (keys->key_1 && !keys->key_1_triggd)
	{
		keys->key_1_triggd = 1;
		if (rules->menu_state == 1)
			rules->menu_state = 2;
		else if (rules->menu_state == 2)
			rules->menu_state = 1;
	}
	else if (keys->key_2 && !keys->key_2_triggd)
	{
		keys->key_2_triggd = 1;
		if (rules->menu_state == 1)
			rules->menu_state = 3;
		else if (rules->menu_state == 3)
			rules->menu_state = 1;
	}
	else if (keys->key_3 && !keys->key_3_triggd)
	{
		keys->key_3_triggd = 1;
		if (rules->menu_state == 1)
			rules->menu_state = 4;
		else if (rules->menu_state == 4)
			rules->menu_state = 1;
	}
}

static void	ft_menu_toggle_and_back(t_keys *keys, t_rules *rules)
{
	if (keys->tab && !keys->tab_triggd)
	{
		keys->tab_triggd = 1;
		rules->menu_state = (rules->menu_state == 0);
	}
	if (rules->menu_state == 0)
		return ;
	if (keys->esc)
	{
		rules->menu_state = (rules->menu_state > 1);
	}
}

void	ft_menu_handler(t_scene *scene, t_mlx_obj *mobj, t_keys *keys, t_rules *rules)
{
	ft_menu_toggle_and_back(keys, rules);
	if (rules->menu_state > 0)
		ft_menu_navigation(keys, rules);
	if (keys->tab_triggd || keys->key_1_triggd
		|| keys->key_2_triggd || keys->key_3_triggd)
	{
		keys->tab = 0;
		keys->key_1 = 0;
		keys->key_2 = 0;
		keys->key_3 = 0;
		ft_mlx_img_update(mobj, scene, rules, 0);
	}
}
