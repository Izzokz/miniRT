/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:27:46 by lumugot           #+#    #+#             */
/*   Updated: 2025/08/09 20:51:03 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

void	ft_display_main_help(t_mlx_obj *mobj)
{
	int	y;
	int	color;

	y = 20;
	color = 0xFFFFFF;
	mlx_string_put(mobj->mlx, mobj->win, 15, y, color, MAIN_MENU);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, OPEN_1);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, OPEN_2);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, OPEN_3);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 30, color, CLOSE_MENU);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 15, color, CLOSE_WINDOW);
}

void	ft_display_movement_help(t_mlx_obj *mobj)
{
	int	y;
	int	color;

	y = 20;
	color = 0xFFFFFF;
	mlx_string_put(mobj->mlx, mobj->win, 15, y, color, MOVEMENTS);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, CAM_MOVES);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, CAM_ROLL);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, MOVE_UP_DOWN);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, CAM_ORIENT);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 30, color, CLOSE_1);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 15, color, CLOSE_MENU);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 15, color, CLOSE_WINDOW);
}

void	ft_display_render_help(t_mlx_obj *mobj)
{
	int	y;
	int	color;

	y = 20;
	color = 0xFFFFFF;
	mlx_string_put(mobj->mlx, mobj->win, 15, y, color, RENDER_OPTIONS);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, CHANGE_COLOR);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, FULL_RENDER);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, RESET_MRT_COLOR);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, R_CAM_MIN);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, R_CAM_MAX);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, ALL_RESET);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 30, color, CLOSE_2);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 15, color, CLOSE_MENU);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 15, color, CLOSE_WINDOW);
}

void	ft_display_object_help(t_mlx_obj *mobj)
{
	int	y;
	int	color;

	y = 20;
	color = 0xFFFFFF;
	mlx_string_put(mobj->mlx, mobj->win, 15, y, color, OBJECT_OPTIONS);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, LAUNCH_EDITOR);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 30, color, CLOSE_3);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 15, color, CLOSE_MENU);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 15, color, CLOSE_WINDOW);
}
