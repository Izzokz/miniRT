/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:09:23 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/24 15:06:42 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline int	key_enable(int keycode, t_keys *keys)
{
	if (keycode == XK_z)
	{
		keys->z = 1;
		keys->z_triggd = 1;
	}
	else if (keycode == XK_w)
		keys->w = 1;
	else if (keycode == XK_a)
		keys->a = 1;
	else if (keycode == XK_s)
		keys->s = 1;
	else if (keycode == XK_d)
		keys->d = 1;
	else if (keycode == XK_space)
		keys->space = 1;
	else if (keycode == XK_Shift_L)
		keys->shift = 1;
	else if (keycode == XK_Up)
		keys->up = 1;
	else if (keycode == XK_Down)
		keys->down = 1;
	else if (keycode == XK_Left)
		keys->left = 1;
	else if (keycode == XK_Right)
		keys->right = 1;
	else if (keycode == XK_Control_L)
		keys->ctrl = 1;
	else if (keycode == XK_Escape)
		keys->esc = 1;
	else if (keycode == XK_r)
		keys->r = 1;
	else if (keycode == XK_c)
		keys->c = 1;
	else if (keycode == XK_0)
		keys->reset = 1;
	else if (keycode == XK_Tab)
        keys->tab = 1;
	return (0);
}

static inline int	key_disable(int keycode, t_keys *keys)
{
	if (keycode == XK_z)
		keys->z_triggd = 0;
	else if (keycode == XK_w)
		keys->w = 0;
	else if (keycode == XK_a)
		keys->a = 0;
	else if (keycode == XK_s)
		keys->s = 0;
	else if (keycode == XK_d)
		keys->d = 0;
	else if (keycode == XK_space)
		keys->space = 0;
	else if (keycode == XK_Shift_L)
		keys->shift = 0;
	else if (keycode == XK_Up)
		keys->up = 0;
	else if (keycode == XK_Down)
		keys->down = 0;
	else if (keycode == XK_Left)
		keys->left = 0;
	else if (keycode == XK_Right)
		keys->right = 0;
	else if (keycode == XK_Control_L)
		keys->ctrl = 0;
	else if (keycode == XK_r)
		keys->r = 0;
	else if (keycode == XK_c)
		keys->c = 0;
	else if (keycode == XK_0)
		keys->reset = 0;
	else if (keycode == XK_Tab)
    {
        keys->tab = 0;
        keys->tab_triggd = 0;
    }
	return (0);
}

static inline int	loop(uintptr_t objscenekeys[3])
{
	if (((t_keys *)(void *)*(objscenekeys + 2))->esc)
	{
		free_scene((t_scene *)(void *)*(objscenekeys + 1));
		ft_free_mlx_obj((t_mlx_obj *)(void *)*objscenekeys);
		exit(0);
	}
	ft_mlx_key_hook((t_mlx_obj *)(void *)*objscenekeys,
		(t_scene *)(void *)*(objscenekeys + 1),
		(t_keys *)(void *)*(objscenekeys + 2));
	return (0);
}

static inline int	quit(uintptr_t objscenekeys[3])
{
	ft_free_mlx_obj((t_mlx_obj *)(void *)*objscenekeys);
	free_scene((t_scene *)(void *)*(objscenekeys + 1));
	exit(0);
}

inline void	ft_mlx_loop(t_mlx_obj *mobj, t_scene *scene)
{
	static t_keys	keys = (t_keys){0};
	uintptr_t		objscenekeys[3];

	*objscenekeys = (uintptr_t)(void *)mobj;
	*(objscenekeys + 1) = (uintptr_t)(void *)scene;
	*(objscenekeys + 2) = (uintptr_t)(void *)&keys;
	mlx_hook(mobj->win, 17, 0, quit, objscenekeys);
	mlx_hook(mobj->win, 3, 1L << 1, key_disable, &keys);
	mlx_hook(mobj->win, 2, 1L << 0, key_enable, &keys);
	mlx_loop_hook(mobj->mlx, loop, objscenekeys);
	mlx_loop(mobj->mlx);
}
