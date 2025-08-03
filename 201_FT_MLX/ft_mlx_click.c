/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_click.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 07:07:29 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/03 14:08:28 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

inline int	ft_mlx_click(int button, int x, int y, uintptr_t objscene[2])
{
	t_vec	scaled[2];
	t_obj	*hit;

	ft_vec_scale(*scaled, ((t_scene *)(void *)*(objscene + 1))->vp->hor,
		(x + .5) * (1.0 / ((t_mlx_obj *)(void *)*objscene)->win_i));
	ft_vec_scale(*(scaled + 1), ((t_scene *)(void *)*(objscene + 1))->vp->ver,
		(y + .5) * (1.0 / ((t_mlx_obj *)(void *)*objscene)->win_j));
	ft_shoot_ray(((t_scene *)(void *)*(objscene + 1))->ray,
		(void *)*(objscene + 1), scaled);
	hit = ft_hit_nearest_obj(((t_scene *)(void *)*(objscene + 1))->ray,
			((t_scene *)(void *)*(objscene + 1))->objects);
	if (hit)
	{
		if (button == 1)
			printf("enter edit mode\n");
		else if (button == 3)
			printf("enter color mode\n");
		else if (button == 2)
			printf("duplicate object\n");
	}
	return (0);
}
