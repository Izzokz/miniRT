/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:54:10 by lumugot           #+#    #+#             */
/*   Updated: 2025/08/11 22:28:21 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <errno.h>
# include <stdint.h>
# include <X11/keysym.h>
# include "../mlx-linux/mlx.h"
# include "typedef.h"
# include "ft_mlx.h"
# include "parse.h"
# include "ft_vec.h"
# include "ft_obj.h"
# include "ft_process.h"
# include "ft_editor.h"
# include "menu.h"

void				ft_set_const_cam(const t_camera *cam);
const t_camera		*ft_get_const_cam(void);

#endif
