/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:12:26 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/12 11:28:36 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

inline void	ft_put_color(t_mlx_obj *mobj,
	int x, int y, unsigned int color)
{
	char	*dst;

	dst = mobj->img_data + (y * mobj->size_line + x * (mobj->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	ft_init_up_vec(t_vec up, const t_vec forward)
{
	if (fabs(forward[1]) > 0.99)
		ft_new_vec(up, 0, 0, 1);
	else
		ft_new_vec(up, 0, 1, 0);
}

static void	ft_init_right_up(
	t_vec right, t_vec up, const t_vec forward)
{
	ft_vec_cross(right, up, forward);
	ft_vec_norm(right, right);
	ft_vec_cross(up, forward, right);
	ft_vec_norm(up, up);
}

static void	ft_init_roll(t_vec right, t_vec up, double roll)
{
	double	cr;
	double	sr;
	t_vec	right_rot;
	t_vec	up_rot;

	cr = cos(roll);
	sr = sin(roll);
	right_rot[0] = cr * right[0] - sr * up[0];
	right_rot[1] = cr * right[1] - sr * up[1];
	right_rot[2] = cr * right[2] - sr * up[2];
	up_rot[0] = sr * right[0] + cr * up[0];
	up_rot[1] = sr * right[1] + cr * up[1];
	up_rot[2] = sr * right[2] + cr * up[2];
	ft_cpy_vec(right, right_rot);
	ft_cpy_vec(up, up_rot);
}

inline void	ft_init_cam_vectors(t_vec cam_vectors[3], const t_scene *s)
{
	double	win_ratio;
	double	plane_h;
	t_vec	tmp1;
	t_vec	tmp2;

	win_ratio = (double)WIDTH / (double)HEIGHT;
	plane_h = tan(s->camera.fov * 0.5 * (PI / 180.0)) * 2.0;
	ft_cpy_vec(tmp1, s->_forward);
	ft_init_up_vec(tmp2, tmp1);
	ft_init_right_up(cam_vectors[0], tmp2, tmp1);
	ft_init_roll(cam_vectors[0], tmp2, s->_roll);
	ft_vec_scale(cam_vectors[0], cam_vectors[0], plane_h * win_ratio);
	ft_vec_scale(cam_vectors[1], tmp2, plane_h);
	ft_vec_scale(tmp1, s->_forward, 2.0);
	ft_vec_sub(cam_vectors[2], s->camera.pos, tmp1);
}
