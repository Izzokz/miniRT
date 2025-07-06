/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_key_hook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:41:45 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/06 22:54:58 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline void	ft_set_rules_max(t_rules *rules)
{
	rules->ref = 4;
	rules->ref_str = .75;
	rules->pixel_cross = 1;
	rules->coloration = NULL;
}

static inline void	ft_move2(const char x, const char y,
	const char z, t_scene *scene)
{
	t_vec	move;
	t_vec	tmp[3];
	t_vec	up;

	ft_new_vec(up, 0, 1, 0);
	ft_new_vec(move, x, y, z);
	ft_vec_norm(*(tmp + 2), scene->camera.orientation);
	ft_vec_cross(*tmp, up, *(tmp + 2));
	ft_vec_norm(*tmp, *tmp);
	ft_vec_scale(*tmp, *tmp, *move);
	ft_vec_scale(up, up, *(move + 1));
	ft_vec_scale(*(tmp + 2), *(tmp + 2), *(move + 2));
	ft_vec_add(*(tmp + 1), *tmp, up);
	ft_vec_add(*(tmp + 1), *(tmp + 1), *(tmp + 2));
	ft_vec_norm(*(tmp + 1), *(tmp + 1));
	ft_vec_scale(*(tmp + 1), *(tmp + 1), MOVE_SPEED);
	ft_vec_add(scene->camera.pos, scene->camera.pos, *(tmp + 1));
}

static inline char	ft_move(unsigned char keys, t_scene *scene)
{
	char	x;
	char	y;
	char	z;

	x = ((keys >> 0) & 1) - ((keys >> 1) & 1);
	y = ((keys >> 2) & 1) - ((keys >> 3) & 1);
	z = ((keys >> 4) & 1) - ((keys >> 5) & 1);
	if (!(!!x + !!y + !!z))
		return (0);
	ft_move2(x, y, z, scene);
	return (1);
}

static inline void	ft_rotate_vec(t_vec v, const t_vec axis, const float angle)
{
	t_vec	tmp;
	t_vec	tmp2;
	float	cos_a;
	float	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	ft_vec_scale(tmp, v, cos_a);
	ft_vec_cross(tmp2, axis, v);
	ft_vec_scale(tmp2, tmp2, sin_a);
	ft_vec_add(v, tmp, tmp2);
	ft_vec_scale(tmp, axis, ft_vec_dot(axis, v) * (1 - cos_a));
	ft_vec_add(v, v, tmp);
}

static inline char	ft_rotate(const t_keys keys, t_scene *scene)
{
	float	yaw;
	float	pitch;
	t_vec	right;
	t_vec	up;

	yaw = ((keys.left > 0) - (keys.right > 0)) * ROT_SPEED;
	pitch = ((keys.up > 0) - (keys.down > 0)) * ROT_SPEED;
	if (yaw == 0 && pitch == 0)
		return (0);
	ft_new_vec(up, 0, 1, 0);
	if (yaw != 0)
		ft_rotate_vec(scene->camera.orientation, up, yaw);
	if (pitch != 0)
	{
		ft_vec_cross(right, up, scene->camera.orientation);
		ft_vec_norm(right, right);
		ft_rotate_vec(scene->camera.orientation, right, pitch);
	}
	ft_vec_norm(scene->camera.orientation, scene->camera.orientation);
	return (1);
}

void	ft_mlx_key_hook(const t_keys keys, t_scene *scene, t_mlx_obj *mobj)
{
    static t_rules	rules;
    static char		init = 0;
    char			has_changed;

    if (!init)
    {
        ++init;
        ft_set_rules_max(&rules);
        ft_mlx_img_update(mobj, scene, &rules);
        return ;
    }
    has_changed = ft_move(*(unsigned char *)&keys, scene);
    if (ft_rotate(keys, scene))
        has_changed = 1;
    if (has_changed)
    {
        ft_mlx_img_update(mobj, scene, &rules);
    }
    else if (keys.r)
    {
        ft_set_rules_max(&rules);
        ft_mlx_img_update(mobj, scene, &rules);
    }
}
