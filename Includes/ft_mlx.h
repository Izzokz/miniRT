/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:08:38 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/06/23 16:08:39 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MLX_H
# define FT_MLX_H

/* MLX INIT AND FREE */
t_mlx_obj	*ft_mlx_obj_init(void);
void		ft_free_mlx_obj(t_mlx_obj *mobj);

/* MLX LOOP */
void		ft_mlx_key_hook(const t_keys keys, t_scene *scene);
void		ft_mlx_loop(const t_mlx_obj *mobj, t_scene *scene);

#endif
