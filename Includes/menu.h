/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:22:51 by lumugot           #+#    #+#             */
/*   Updated: 2025/07/25 11:37:44 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

# include "miniRT.h"

// Faire les defines pour les différents message du menu et pour la norme :)

//display_menu.c
void	ft_display_main_help(t_mlx_obj *mobj);
void	ft_display_movement_help(t_mlx_obj *mobj);
void	ft_display_render_help(t_mlx_obj *mobj);
void	ft_display_object_help(t_mlx_obj *mobj);

#endif