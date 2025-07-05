/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_key_hook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 19:41:45 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/06/23 19:41:46 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline void	ft_set_rules_max(t_rules *rules)
{
	rules->ref = 4;
	rules->ref_str = .75;
	rules->pixel_cross = 1;
	rules->coloration = NULL; // max coloration
}

static inline void	ft_move2(const char x, const char y,
	const char z, t_scene *scene)
{
	t_vec	move;
	t_vec	tmp[3];
	char	count;
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
	count = !!x + !!y + !!z;
	if (count > 0)
		ft_vec_scale(*(tmp + 1), *(tmp + 1), 1.0 / count);
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

void	ft_mlx_key_hook(const t_keys keys, t_scene *scene, t_mlx_obj *mobj)
{
	static t_rules	rules;
	static char		init = 0;

	if (!init)
	{
		++init;
		ft_set_rules_max(&rules);
		ft_mlx_img_update(mobj, scene, &rules);
	}
	else if (ft_move(*(unsigned char *)&keys, scene))
	{
//		rules.ref = 1;
//		rules.pixel_cross = 16;
//		rules.coloration = NULL; // min coloration
		printf("X%fY%fZ%f\n", scene->camera.pos[0], scene->camera.pos[1], scene->camera.pos[2]);
		ft_mlx_img_update(mobj, scene, &rules);
	}
	else if (keys.r)
	{
		ft_set_rules_max(&rules);
		ft_mlx_img_update(mobj, scene, &rules);
	}
}
