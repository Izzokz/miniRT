/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:33:06 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/24 15:39:00 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline void	ft_get_viewport(t_scene *s, int i[2], char zoom)
{
	double	tmp_width;
	double	tmp_height;
	t_vec	ruf[3];
	t_vec	tmp;

	ft_cpy_vec(*(ruf + 2), s->camera.orientation);
	ft_vec_cross(*ruf, s->_up, *(ruf + 2));
	ft_vec_norm(*ruf, *ruf);
	ft_vec_cross(*(ruf + 1), *(ruf + 2), *ruf);
	ft_vec_norm(*(ruf + 1), *(ruf + 1));
	tmp_width = 2 * tan((s->camera.fov / (zoom + 1)) * (PI / 360.0));
	tmp_height = tmp_width * ((double)*(i + 1) / *i);
	ft_vec_scale(*(t_vec *)s->vp, *ruf, tmp_width);
	ft_vec_scale(*(((t_vec *)s->vp) + 1), *(ruf + 1), -tmp_height);
	ft_vec_add(*ruf, s->camera.pos, *(ruf + 2));
	ft_vec_div(tmp, *((t_vec *)s->vp), 2);
	ft_vec_sub(*ruf, *ruf, tmp);
	ft_vec_div(tmp, *(((t_vec *)s->vp) + 1), 2);
	ft_vec_sub(*(((t_vec *)s->vp) + 2), *ruf, tmp);
}

static void	ft_display_help(t_mlx_obj *mobj)
{
    int	y;
    int	color;

    y = 20;
    color = 0xFFFFFF;
    mlx_string_put(mobj->mlx, mobj->win, 15, y, color, "--- HELP MENU ---");
    mlx_string_put(mobj->mlx, mobj->win, 15, y += 20,
		color, "Setup les touches");
    mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, "Touche 1");
    mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, "Touche 2");
    mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, "Touche ...");
    mlx_string_put(mobj->mlx, mobj->win, 15, y += 20, color, "ESC: Exit");
}

inline void	ft_mlx_img_update(t_mlx_obj *mobj, t_scene *scene,
	t_rules *rules, int rerender)
{
    if (rerender)
    {
        ft_get_viewport(scene, (int *)mobj, rules->zoom);
        ft_putstr_fd("\r\e[94;7mR\e[0m  ", 1);
        ft_process(mobj, scene, rules);
        ft_putstr_fd("\r\e[94;7mR\e[0m\e[32;1mOK\e[0m", 1);
    }
    mlx_put_image_to_window(mobj->mlx, mobj->win, mobj->img, 0, 0);
    if (rules->show_help)
        ft_display_help(mobj);
    else
        mlx_string_put(mobj->mlx, mobj->win, 15, 20, 0xFFFFFF,
            "Press TAB for help");
}
