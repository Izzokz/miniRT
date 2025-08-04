/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:09:23 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/04 23:41:42 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline int	key_enable(int keycode, t_keys *keys)
{
	if (keycode == XK_w)
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
	else if (keycode == XK_t)
		keys->t = 1;
	else if (keycode == XK_1)
        keys->key_1 = 1;
    else if (keycode == XK_2)
        keys->key_2 = 1;
	else if (keycode == XK_3)
        keys->key_3 = 1;
	else if (keycode == XK_q)
    	keys->q = 1;
	else if (keycode == XK_e)
    	keys->e = 1;
	else if (keycode == XK_F1)	
		keys->p_up = 1;
	else if (keycode == XK_F2)
		keys->p_down = 1;
	else if (keycode == XK_F11)
		keys->r_speed_up = 1;
	else if (keycode == XK_F12)
		keys->r_speed_down = 1;
	return (0);
}

static inline int	key_disable(int keycode, t_keys *keys)
{
	if (keycode == XK_w)
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
	else if (keycode == XK_t)
		keys->t = 0;
    else if (keycode == XK_1)
    {
        keys->key_1 = 0;
        keys->key_1_triggd = 0;
    }
    else if (keycode == XK_2)
    {
        keys->key_2 = 0;
        keys->key_2_triggd = 0;
    }
	else if (keycode == XK_3)
    {
        keys->key_3 = 0;
        keys->key_3_triggd = 0;
    }
    else if (keycode == XK_q)
        keys->q = 0;
    else if (keycode == XK_e)
        keys->e = 0;
	else if (keycode == XK_F1)
		keys->p_up = 0;
	else if (keycode == XK_F2)
		keys->p_down = 0;
	else if (keycode == XK_F11)
		keys->r_speed_up = 0;
	else if (keycode == XK_F12)
		keys->r_speed_down = 0;
    return (0);
}

static inline int	loop(uintptr_t objscenekeys[3])
{
	if (((t_keys *)(void *)*(objscenekeys + 2))->esc)
	{
		write(1, "\n", 1);
		free_scene((t_scene *)(void *)objscenekeys[1]);
		ft_free_mlx_obj((t_mlx_obj *)(void *)*objscenekeys);
		exit(0);
	}
	ft_mlx_key_hook((t_mlx_obj *)(void *)objscenekeys[0],
		(t_scene *)(void *)objscenekeys[1],
		(t_keys *)(void *)objscenekeys[2]);
	return (0);
}

static inline int	quit(uintptr_t objscenekeys[3])
{
	ft_free_mlx_obj((t_mlx_obj *)(void *)objscenekeys[0]);
	free_scene((t_scene *)(void *)objscenekeys[1]);
	exit(0);
}

inline void	ft_mlx_loop(t_mlx_obj *mobj, t_scene *scene)
{
	static t_keys	keys = (t_keys){0};
	uintptr_t		objscenekeys[3];

	objscenekeys[0] = (uintptr_t)(void *)mobj;
	objscenekeys[1] = (uintptr_t)(void *)scene;
	objscenekeys[2] = (uintptr_t)(void *)&keys;
	mlx_hook(mobj->win, 17, 0, quit, objscenekeys);
	mlx_hook(mobj->win, 3, 1L << 1, key_disable, &keys);
	mlx_hook(mobj->win, 2, 1L << 0, key_enable, &keys);
	mlx_loop_hook(mobj->mlx, loop, objscenekeys);
	mlx_loop(mobj->mlx);
}
