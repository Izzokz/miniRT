/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:22:51 by lumugot           #+#    #+#             */
/*   Updated: 2025/07/31 13:35:30 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

# include "miniRT.h"

# define MAIN_MENU "--- MAIN MENU ---"
# define MOVEMENTS "--- MOVEMENTS ---"
# define RENDER_OPTIONS "--- RENDER OPTIONS ---"
# define OBJECT_OPTIONS "--- OBJECT OPTIONS ---"
# define CAM_MOVES "WASD: Move the camera position"
# define MOVE_UP_DOWN "SHIFT / SPACE: Move Up / Down"
# define CAM_ORIENT "ARROWS: Orient the camera"
# define OPEN_1 "1. Movement commands"
# define OPEN_2 "2. Render options"
# define OPEN_3 "3. Object options"
# define CLOSE_1 "1: Close the submenu"
# define CLOSE_2 "2: Close the submenu"
# define CLOSE_3 "3: Close the submenu"
# define CLOSE_MENU "TAB: Close the menu"
# define CLOSE_WINDOW "ESC: Close the window"

// display_menu.c
void	ft_display_main_help(t_mlx_obj *mobj);
void	ft_display_movement_help(t_mlx_obj *mobj);
void	ft_display_render_help(t_mlx_obj *mobj);
void	ft_display_object_help(t_mlx_obj *mobj);

// ft_mlx_menu.c
void	ft_display_menu(t_mlx_obj *mobj, t_rules *rules);
void	ft_menu_handler(t_keys *keys, t_rules *rules);

#endif