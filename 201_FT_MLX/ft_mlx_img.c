/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:33:06 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/04 15:18:22 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline void	ft_get_viewport(t_vec viewport[3], t_camera cam,
	int i, int j)
{
	double		tmp_width;
	double		tmp_height;
	t_vec		tmp;
	const t_vec	up = {'\0', 1, '\0'};

	tmp_width = 2 * tan((cam.fov * (PI / 180.0)) / 2);
	tmp_height = tmp_width / ((double)j / i);
	ft_vec_cross(tmp, up, cam.orientation);
	ft_vec_norm(tmp, tmp);
	ft_vec_scale(*viewport, tmp, -tmp_width);
	ft_vec_cross(tmp, cam.orientation, tmp);
	ft_vec_scale(*(viewport + 1), tmp, tmp_height);
	ft_vec_add(tmp, cam.pos, cam.orientation);
	ft_vec_div(*(viewport + 2), *viewport, 2);
	ft_vec_sub(*(viewport + 2), tmp, *(viewport + 2));
	ft_vec_div(tmp, *(viewport + 1), 2);
	ft_vec_sub(*(viewport + 2), *(viewport + 2), tmp);
}

/* Used for final result. */
void	ft_mlx_img_print(t_scene *scene, t_mlx_obj *mlx)
{
	t_vec	vp[3];
	t_rules	rules;

	rules = (t_rules){.ref = 4, .pixel_cross = 1,
		.ref_str = .5, .coloration = /*ft_color_full*/NULL};
	ft_get_viewport(vp, scene->camera, mlx->win_i, mlx->win_j);
	ft_process(mlx, (t_viewport *)vp, scene, rules);
	printf("IMAGE GENERATED.\n");
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

/* Used while moving. */
inline void	ft_mlx_img_update(t_scene *scene, t_mlx_obj *mlx)
{
	t_vec	vp[3];
	t_rules	rules;

	rules = (t_rules){.ref = 0, .pixel_cross = 16,
		.coloration = /*ft_color_minimal*/NULL};
	ft_get_viewport(vp, scene->camera, mlx->win_i, mlx->win_j);
	ft_process(mlx, (t_viewport *)vp, scene, rules);
	printf("MOVEMENT.\n");
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}
