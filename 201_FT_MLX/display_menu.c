/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:27:46 by lumugot           #+#    #+#             */
/*   Updated: 2025/07/25 11:48:57 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

void	ft_display_main_help(t_mlx_obj *mobj)
{
	int	y;
	int	color;

	y = 20;
	color = 0xFFFFFF;
	mlx_string_put(mobj->mlx, mobj->win, 15, y, color, "--- MENU PRINCIPAL ---");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, "1. Commandes de deplacement");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, "2. Options de rendu");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, "3. Options des objets");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 30, color, "TAB: Fermer le menu");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 15, color, "ESC: Fermez la fenêtre");
}

void	ft_display_movement_help(t_mlx_obj *mobj)
{
	int	y;
	int	color;

	y = 20;
	color = 0xFFFFFF;
	mlx_string_put(mobj->mlx, mobj->win, 15, y, color, "--- DEPLACEMENTS ---");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, "WASD : Bouger la camera");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, "SHIFT / SPACE : Monter / Descendre");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, "FLECHES : Orienter la camera");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 30, color, "TAB: Fermer le menu");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 15, color, "ESC: fermez la fenêtre");
}

void	ft_display_render_help(t_mlx_obj *mobj)
{
	int	y;
	int	color;

	y = 20;
	color = 0xFFFFFF;
	mlx_string_put(mobj->mlx, mobj->win, 15, y, color, "--- OPTIONS DE RENDU ---");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, "C : Changer la coloration");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, "R : Activer le render (MAX_QUALITY)");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 30, color, "TAB: Fermer le menu");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 15, color, "ESC: fermez la fenêtre");
}

void	ft_display_object_help(t_mlx_obj *mobj)
{
	int	y;
	int	color;

	y = 20;
	color = 0xFFFFFF;
	mlx_string_put(mobj->mlx, mobj->win, 15, y, color, "--- OPTIONS DES OBJECTS ---");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, "Mettre les touches pour le changement des objs");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 30, color, "TAB: Fermer le menu");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 15, color, "ESC: fermez la fenêtre");
}
