/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:10:35 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/11 19:32:28 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
