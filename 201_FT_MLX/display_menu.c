/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:27:46 by lumugot           #+#    #+#             */
/*   Updated: 2025/07/31 12:10:05 by lumugot          ###   ########.fr       */
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
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, "C : Changer la coloration");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, "R : Activer le render (MAX_QUALITY)");
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
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, "Mettre les touches pour le changement des objs");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 30, color, CLOSE_3);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 15, color, CLOSE_MENU);
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 15, color, CLOSE_WINDOW);
}
