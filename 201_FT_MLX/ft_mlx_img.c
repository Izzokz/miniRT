/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:33:06 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/27 11:48:06 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline void	ft_get_viewport(t_vec viewport[3], t_scene *scene,
	int i[2], char zoom)
{
	double	tmp_width;
	double	tmp_height;
	t_vec	cam_basis[3];
	t_vec	center_point;

	ft_cpy_vec(cam_basis[2], scene->camera.orientation);
	ft_vec_cross(cam_basis[0], scene->_up, cam_basis[2]);
	ft_vec_norm(cam_basis[0], cam_basis[0]);
	ft_vec_cross(cam_basis[1], cam_basis[2], cam_basis[0]);
	ft_vec_norm(cam_basis[1], cam_basis[1]);
	tmp_width = 2 * tan((scene->camera.fov / (zoom + 1)) * (PI / 360.0));
	tmp_height = tmp_width * ((double)i[1] / i[0]);
	ft_vec_scale(viewport[0], cam_basis[0], tmp_width);
	ft_vec_scale(viewport[1], cam_basis[1], tmp_height);
	ft_vec_add(center_point, scene->camera.pos, cam_basis[2]);
	ft_vec_div(cam_basis[0], viewport[0], 2);
	ft_vec_sub(center_point, center_point, cam_basis[0]);
	ft_vec_div(cam_basis[1], viewport[1], 2);
	ft_vec_sub(viewport[2], center_point, cam_basis[1]);
}

inline void	ft_mlx_img_update(t_mlx_obj *mobj, t_scene *scene, t_rules *rules, int rerender)
{
	t_vec	vp[3];

	if (rerender)
	{
		ft_get_viewport(vp, scene, (int *)mobj, rules->zoom);
		ft_putstr_fd("\r\e[94;7mR\e[0m  ", 1);
		ft_process(mobj, (t_viewport *)vp, scene, rules);
		ft_putstr_fd("\r\e[94;7mR\e[0m\e[32;1mOK\e[0m", 1);
	}
	mlx_put_image_to_window(mobj->mlx, mobj->win, mobj->img, 0, 0);
	ft_display_menu(mobj, rules);
}
