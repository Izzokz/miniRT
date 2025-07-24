/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:08:38 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/24 15:01:44 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MLX_H
# define FT_MLX_H

# include "typedef.h"

/* MLX INIT AND FREE */
t_mlx_obj	*ft_mlx_obj_init(void);
void		ft_free_mlx_obj(t_mlx_obj *mobj);

/* MLX LOOP */
void		ft_mlx_key_hook(t_mlx_obj *mobj, t_scene *scene, t_keys *keys);
void		ft_mlx_loop(t_mlx_obj *mobj, t_scene *scene);

/* MLX IMG */
void	ft_mlx_img_update(t_mlx_obj *mobj, t_scene *scene, t_rules *rules, int rerender);
#endif
