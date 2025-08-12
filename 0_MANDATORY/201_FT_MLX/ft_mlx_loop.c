/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 20:09:23 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/12 11:30:44 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline int	key_enable(int keycode, uint32_t *keys)
{
	static const int	keys_list[26] = {XK_a, XK_d, XK_Shift_L, XK_space,
		XK_s, XK_w, XK_Left, XK_Right, XK_Down, XK_Up, XK_q, XK_e, XK_Control_L,
		XK_Escape, XK_r, XK_c, XK_0, XK_Tab, XK_t, XK_1, XK_2, XK_3, XK_F1,
		XK_F2, XK_F11, XK_F12};
	char				i;

	i = -1;
	while (++i < 26)
	{
		if (*(keys_list + i) == keycode)
		{
			*keys |= (1u << i);
			break ;
		}
	}
	return (0);
}

static inline int	key_disable(int keycode, uint32_t *keys)
{
	static const int	keys_list[26] = {XK_a, XK_d, XK_Shift_L, XK_space,
		XK_s, XK_w, XK_Left, XK_Right, XK_Down, XK_Up, XK_q, XK_e, XK_Control_L,
		XK_Escape, XK_r, XK_c, XK_0, XK_Tab, XK_t, XK_1, XK_2, XK_3, XK_F1,
		XK_F2, XK_F11, XK_F12};
	char				i;

	i = -1;
	while (++i < 26)
	{
		if (*(keys_list + i) == keycode)
		{
			*keys &= ~(1u << i);
			break ;
		}
	}
	if (keycode == XK_Tab)
		((t_keys *)keys)->tab_triggd = 0;
	else if (keycode == XK_1)
		((t_keys *)keys)->key_1_triggd = 0;
	else if (keycode == XK_2)
		((t_keys *)keys)->key_2_triggd = 0;
	else if (keycode == XK_3)
		((t_keys *)keys)->key_3_triggd = 0;
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
