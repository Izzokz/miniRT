/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:24:51 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/04 14:26:18 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PROCESS_H
# define FT_PROCESS_H

# include "typedef.h"

t_obj			*ft_hit_nearest_obj(t_ray, const t_obj *head);
t_obj			*ft_hit_nearest_obj_nb(const t_ray, const t_obj *head);
void			ft_color_mult(t_color edit, const t_color m1, const t_color m2);
void			ft_color_scale(t_color edit, const float factor);
void			ft_color_add(t_color edit, const t_color sum);
void			ft_color_reflect(t_color edit, const t_color base,
					const float multiplicator);
unsigned int	ft_convert_color(const t_color color);
unsigned int	ft_blend_color(t_ray, t_obj *hit,
					const t_scene *scene, const t_rules *rules);
unsigned int	ft_color_mini(t_ray, t_obj *hit,
					const t_scene *scene, const t_rules *rules);
unsigned int	ft_color_glass(t_ray, t_obj *hit,
					const t_scene *scene, const t_rules *rules);
unsigned int	ft_unicorn(t_ray, t_obj *hit,
					const t_scene *scene, const t_rules *rules);
unsigned int	ft_color_virus(t_ray, t_obj *hit,
					const t_scene *scene, const t_rules *rules);
unsigned int	ft_color_chill(t_ray, t_obj *hit,
					const t_scene *scene, const t_rules *rules);
unsigned int	ft_color_error(t_ray, t_obj *hit,
					const t_scene *scene, const t_rules *rules);
void			ft_process(t_mlx_obj *mobj,
					t_scene *scene, const t_rules *rules);
void			ft_shoot_ray(t_ray,
					const t_scene *scene, const t_vec scaled[2]);

#endif
