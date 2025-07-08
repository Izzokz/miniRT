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
	double		tmp_width;
	double		tmp_height;
	t_vec		tmp;
	const t_vec	up = {'\0', 1, '\0'};

	tmp_width = 2 * tan(scene->camera.fov * (PI / 360.0));
	tmp_height = tmp_width * ((double)i / j);
	ft_vec_cross(tmp, up, scene->camera.orientation);
	ft_vec_norm(tmp, tmp);
	ft_vec_scale(*viewport, tmp, tmp_width);
	ft_vec_cross(tmp, scene->camera.orientation, tmp);
	ft_vec_scale(*(viewport + 1), tmp, -tmp_height);
	ft_vec_add(tmp, scene->camera.pos, scene->camera.orientation);
	ft_vec_div(*(viewport + 2), *viewport, 2);
	ft_vec_sub(*(viewport + 2), tmp, *(viewport + 2));
	ft_vec_div(tmp, *(viewport + 1), 2);
	ft_vec_sub(*(viewport + 2), *(viewport + 2), tmp);
}

inline void	ft_mlx_img_update(t_mlx_obj *mobj, t_scene *scene, t_rules *rules)
{
	t_vec	vp[3];

	ft_get_viewport(vp, scene, mobj->win_i, mobj->win_j);
	ft_process(mobj, (t_viewport *)vp, scene, rules);
	mlx_put_image_to_window(mobj->mlx, mobj->win, mobj->img, 0, 0);
}
