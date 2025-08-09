/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:22:51 by lumugot           #+#    #+#             */
/*   Updated: 2025/08/09 21:47:46 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

# include "miniRT.h"

# define MAIN_MENU "--- MAIN MENU ---"
# define MOVEMENTS "--- MOVEMENTS ---"
# define RENDER_OPTIONS "--- RENDER OPTIONS ---"
# define OBJECT_OPTIONS "--- OBJECT OPTIONS ---"
# define BOOST_SPEED "F1/F2: Speed up / Slow down movement"
# define BOOST_ROT   "F11/F12: Speed up / Slow down rotation"
# define CAM_MOVES "WASD: Move the camera position on the x axis"
# define CAM_ROLL "QE: Turn left (Q) and right (E) on the Z axis"
# define MOVE_UP_DOWN "SHIFT / SPACE:  Move Up / Down on the y axis"
# define CAM_ORIENT "ARROWS: Orient the camera"
# define OPEN_1 "1. Movement commands"
# define OPEN_2 "2. Render options"
# define OPEN_3 "3. Object options"
# define CLOSE_1 "1: Close the submenu"
# define CLOSE_2 "2: Close the submenu"
# define CLOSE_3 "3: Close the submenu"
# define CLOSE_MENU "TAB: Close the menu"
# define CLOSE_WINDOW "ESC: Close the window"
# define FULL_RENDER "R: Enable render (MAX_QUALITY)"
# define CHANGE_COLOR "C: Change coloring"
# define RESET_MRT_COLOR "CTRL + C: Reset to MRT_BEST_COLOR"
# define R_CAM_MIN "CTRL + R: Reset camera + render min quality"
# define R_CAM_MAX "CTRL + SHIFT + R: Reset camera + render max quality"
# define ALL_RESET "0 + R: Reset cam + reset coloration + render max quality"
# define LAUNCH_EDITOR "T: Open editor's objet in terminal"

// display_menu.c
void	ft_display_main_help(t_mlx_obj *mobj);
void	ft_display_movement_help(t_mlx_obj *mobj);
void	ft_display_render_help(t_mlx_obj *mobj);
void	ft_display_object_help(t_mlx_obj *mobj);

// ft_mlx_menu.c
void	ft_display_menu(t_mlx_obj *mobj, t_rules *rules);
void	ft_menu_handler(t_scene *scene, t_mlx_obj *mobj, t_keys *keys,
			t_rules *rules);

#endif