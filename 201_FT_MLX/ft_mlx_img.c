/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:33:06 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/04 23:43:36 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

// static inline void	print_vec(const t_vec v)
// {
// 	printf("{%f, %f, %f}\n", *v, v[1], v[2]);
// }

inline void	ft_mlx_img_update(t_mlx_obj *mobj, t_scene *scene,
	t_rules *rules, int rerender)
{
	if (rerender)
	{
		ft_putstr_fd("\r\e[94;7mR\e[0m     ", 1);
		ft_process(mobj, scene, rules);
	}
	mlx_put_image_to_window(mobj->mlx, mobj->win, mobj->img, 0, 0);
	ft_display_menu(mobj, rules);
}
