/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 12:54:10 by lumugot           #+#    #+#             */
/*   Updated: 2025/08/11 18:57:36 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include <math.h>
# include <errno.h>
# include <stdint.h>
# include <X11/keysym.h>
# include "mlx.h"
# include "typedef_bonus.h"
# include "ft_mlx_bonus.h"
# include "parse_bonus.h"
# include "ft_vec_bonus.h"
# include "ft_obj_bonus.h"
# include "ft_process_bonus.h"
# include "ft_editor_bonus.h"
# include "menu_bonus.h"

void				ft_set_const_cam(const t_camera *cam);
const t_camera		*ft_get_const_cam(void);

#endif
