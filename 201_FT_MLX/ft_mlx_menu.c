/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:03:12 by lumugot           #+#    #+#             */
/*   Updated: 2025/07/24 17:29:03 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

static void	ft_display_main_help(t_mlx_obj *mobj)
{
	int	y;
	int	color;

	y = 20;
	color = 0xFFFFFF;
	mlx_string_put(mobj->mlx, mobj->win, 15, y, color, "--- MENU PRINCIPAL ---");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, "1. Commandes de deplacement");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, "2. Options de rendu");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 30, color, "TAB: Fermer le menu");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 15, color, "ESC: Quitter le programme");
}

static void	ft_display_movement_help(t_mlx_obj *mobj)
{
	int	y;
	int	color;

	y = 20;
	color = 0xFFFFFF;
	mlx_string_put(mobj->mlx, mobj->win, 15, y, color, "--- DEPLACEMENTS ---");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, "ZQSD / WASD : Bouger la camera");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, "A / E : Monter / Descendre");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, "Fleches : Orienter la camera");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 30, color, "ESC: Retour au menu principal");
}

static void	ft_display_render_help(t_mlx_obj *mobj)
{
	int	y;
	int	color;

	y = 20;
	color = 0xFFFFFF;
	mlx_string_put(mobj->mlx, mobj->win, 15, y, color, "--- OPTIONS DE RENDU ---");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, "C : Changer la coloration");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, "R : Reinitialiser la scene");
	mlx_string_put(mobj->mlx, mobj->win, 15, y += 30, color, "ESC: Retour au menu principal");
}

void	ft_display_menu(t_mlx_obj *mobj, t_rules *rules)
{
	if (rules->menu_state == 1)
		ft_display_main_help(mobj);
	else if (rules->menu_state == 2)
		ft_display_movement_help(mobj);
	else if (rules->menu_state == 3)
		ft_display_render_help(mobj);
	else if (rules->menu_state == 0)
		mlx_string_put(mobj->mlx, mobj->win, 15, 20, 0xFFFFFF,
			"Press TAB to display the key menu");
}

int	ft_menu_handler(t_keys *keys, t_rules *rules)
{
    if (keys->tab && !keys->tab_triggd)
    {
        keys->tab_triggd = 1;
        rules->menu_state = (rules->menu_state == 0);
        return (1);
    }
    if (rules->menu_state == 0)
        return (0);
    if (keys->esc)
    {
        rules->menu_state = (rules->menu_state > 1);
        return (1);
    }
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
    return (1);
}
