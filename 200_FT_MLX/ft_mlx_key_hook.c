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

void	ft_mlx_key_hook(const t_keys keys, t_scene *scene)
{
	(void) scene;
	if (keys.ctrl)
	{
		if (keys.w)
			write(1, "\e[31mw\e[0m\n", 11);
		if (keys.a)
			write(1, "\e[31ma\e[0m\n", 11);
		if (keys.s)
			write(1, "\e[31ms\e[0m\n", 11);
		if (keys.d)
			write(1, "\e[31md\e[0m\n", 11);
	}
	else
	{
		if (keys.w)
			write(1, "w\n", 2);
		if (keys.a)
			write(1, "a\n", 2);
		if (keys.s)
			write(1, "s\n", 2);
		if (keys.d)
			write(1, "d\n", 2);
	}
}
