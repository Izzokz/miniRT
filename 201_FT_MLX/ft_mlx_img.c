/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:33:06 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/08 16:04:07 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline void	ft_get_viewport(t_vec viewport[3], t_scene *scene,
	int i, int j)
{
	double	tmp_width;
	double	tmp_height;
	t_vec	ruf[3];
	t_vec	tmp;

	ft_cpy_vec(*(ruf + 2), scene->camera.orientation);
	ft_vec_cross(*ruf, scene->_up, *(ruf + 2));
	ft_vec_norm(*ruf, *ruf);
	ft_vec_cross(*(ruf + 1), *(ruf + 2), *ruf);
	ft_vec_norm(*(ruf + 1), *(ruf + 1));
	tmp_width = 2 * tan(scene->camera.fov * (PI / 360.0));
	tmp_height = tmp_width * ((double)j / i);
	ft_vec_scale(*viewport, *ruf, tmp_width);
	ft_vec_scale(*(viewport + 1), *(ruf + 1), -tmp_height);
	ft_vec_add(*ruf, scene->camera.pos, *(ruf + 2));
	ft_vec_div(tmp, *viewport, 2);
	ft_vec_sub(*ruf, *ruf, tmp);
	ft_vec_div(tmp, *(viewport + 1), 2);
	ft_vec_sub(*(viewport + 2), *ruf, tmp);
}

inline void	ft_mlx_img_update(t_mlx_obj *mobj, t_scene *scene, t_rules *rules)
{
	t_vec	vp[3];

	ft_get_viewport(vp, scene, mobj->win_i, mobj->win_j);
	ft_process(mobj, (t_viewport *)vp, scene, rules);
	mlx_put_image_to_window(mobj->mlx, mobj->win, mobj->img, 0, 0);
}
