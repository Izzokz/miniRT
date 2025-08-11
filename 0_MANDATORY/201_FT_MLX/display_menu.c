/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:27:46 by lumugot           #+#    #+#             */
/*   Updated: 2025/08/11 22:26:08 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

void	ft_display_main_help(t_mlx_obj *mobj)
{
	int	y;
	int	menu_c;
	int	title_c;
	int	close_c;

	y = 20;
	title_c = 0x00FF00;
	menu_c = 0x00FFFFF;
	close_c = 0xFF0000;
	mlx_string_put(mobj->mlx, mobj->win, 15, y, title_c, MAIN_MENU);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, menu_c, OPEN_1);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, menu_c, OPEN_2);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, menu_c, OPEN_3);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 30, close_c, CLOSE_MENU);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 15, close_c, CLOSE_WINDOW);
}

void	ft_display_movement_help(t_mlx_obj *mobj)
{
	int	y;
	int	color_i;
	int	title_c;
	int	close_c;

	y = 20;
	title_c = 0x00FF00;
	color_i = 0xFFE4E1;
	close_c = 0xFF0000;
	mlx_string_put(mobj->mlx, mobj->win, 15, y, title_c, MOVEMENTS);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color_i, CAM_MOVES);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color_i, CAM_ROLL);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color_i, MOVE_UP_DOWN);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color_i, CAM_ORIENT);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color_i, BOOST_SPEED);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color_i, BOOST_ROT);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 30, close_c, CLOSE_1);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 15, close_c, CLOSE_MENU);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 15, close_c, CLOSE_WINDOW);
}

void	ft_display_render_help(t_mlx_obj *mobj)
{
	int	y;
	int	color_i;
	int	title_c;
	int	close_c;

	y = 20;
	title_c = 0x00FF00;
	color_i = 0xFFE4E1;
	close_c = 0xFF0000;
	mlx_string_put(mobj->mlx, mobj->win, 15, y, title_c, RENDER_OPTIONS);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color_i, CHANGE_COLOR);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color_i, FULL_RENDER);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color_i, RESET_MRT_COLOR);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color_i, R_CAM_MIN);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color_i, R_CAM_MAX);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color_i, ALL_RESET);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 30, close_c, CLOSE_2);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 15, close_c, CLOSE_MENU);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 15, close_c, CLOSE_WINDOW);
}

void	ft_display_object_help(t_mlx_obj *mobj)
{
	int	y;
	int	color_i;
	int	title_c;
	int	close_c;

	y = 20;
	title_c = 0x00FF00;
	color_i = 0xFFE4E1;
	close_c = 0xFF0000;
	mlx_string_put(mobj->mlx, mobj->win, 15, y, title_c, OBJECT_OPTIONS);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color_i, LAUNCH_EDITOR);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 30, close_c, CLOSE_3);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 15, close_c, CLOSE_MENU);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 15, close_c, CLOSE_WINDOW);
}
