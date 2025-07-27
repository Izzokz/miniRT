/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:10:35 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/26 23:54:42 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

const t_vec	g_right = {1, 0, 0};
const t_vec	g_up = {0, 1, 0};
const t_vec	g_forward = {0, 0, 1};

static inline const t_camera	*ft_const_cam(const t_camera *cam)
{
	static t_camera	*const_cam = (void *)0;

	if (!const_cam && cam)
		const_cam = (t_camera *)cam;
	return (const_cam);
}

inline void	ft_set_const_cam(const t_camera *cam)
{
	ft_const_cam(cam);
}

inline const t_camera	*ft_get_const_cam(void)
{
	return (ft_const_cam((void *)0));
}
