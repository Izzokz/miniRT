/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:24:51 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/11 18:57:20 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PROCESS_BONUS_H
# define FT_PROCESS_BONUS_H

# include "typedef_bonus.h"

// ft_color_utils_bonus.c
void			ft_vec_offset(t_vec newv, const t_vec v1,
					const t_vec v2, const double epsilon);
void			ft_vec_random_sphere(t_vec random, const t_vec lpos);
double			ft_get_lambert(const t_ray hit, const t_vec dir);
void			ft_store(t_ray cat[2], const t_ray r1, const t_ray r2);
void			ft_color_merge(t_color edit, const t_color ambient,
					const t_color diffuse, const t_color specular);

// ft_color_obj_norm_bonus.c
void			ft_obj_normal(const t_obj *obj, const t_vec hit_point,
					t_vec normal, const t_vec ray_dir);

// ft_rules_bonus.c
void			ft_set_rules_max(t_rules *rules, t_rules *max);
void			ft_init_rules(t_rules *rules);
void			ft_set_rules_min(t_mlx_obj *mobj, t_rules *rules);

// ft_move_bonus.c
char			ft_move(unsigned char keys, t_scene *scene);

// ft_rotate2_bonus.c
void			ft_apply_rotation(t_scene *scene);

// ft_rotate_bonus.c
char			ft_rotate(const t_keys keys, t_scene *scene);

// misc
void			ft_color_ads_bug(t_color edit, const t_scene *scene,
					const t_obj *hit);
void			ft_color_fix(t_color edit);
void			ft_color_light_dist(t_color edit, const t_light *light,
					const t_vec oray[2], const t_scene *scene);
void			ft_put_color(t_mlx_obj *mobj,
					int x, int y, unsigned int color);
void			ft_init_cam_vectors(t_vec cam_vectors[3], const t_scene *s);
t_obj			*ft_hit_nearest_obj(t_ray, const t_obj *head);
t_obj			*ft_hit_nearest_obj_nb(const t_ray, const t_obj *head);
void			ft_color_mult(t_color edit, const t_color m1, const t_color m2);
void			ft_color_scale(t_color edit, const float factor);
void			ft_color_add(t_color edit, const t_color sum);
void			ft_color_reflect(t_color edit, const t_color base,
					const float multiplicator);
unsigned int	ft_convert_color(const t_color color);
unsigned int	ft_blend_color(t_ray, t_obj *hit,
					t_scene *scene, const t_rules *rules);
unsigned int	ft_color_mini(t_ray, t_obj *hit,
					t_scene *scene, const t_rules *rules);
unsigned int	ft_color_glass(t_ray, t_obj *hit,
					t_scene *scene, const t_rules *rules);
unsigned int	ft_unicorn(t_ray, t_obj *hit,
					t_scene *scene, const t_rules *rules);
unsigned int	ft_color_virus(t_ray, t_obj *hit,
					t_scene *scene, const t_rules *rules);
unsigned int	ft_color_chill(t_ray, t_obj *hit,
					t_scene *scene, const t_rules *rules);
unsigned int	ft_color_error(t_ray, t_obj *hit,
					t_scene *scene, const t_rules *rules);
void			ft_process(t_mlx_obj *mobj,
					t_scene *scene, const t_rules *rules);
void			ft_shoot_ray(t_ray,
					const t_scene *scene, const t_vec scaled[2]);

#endif
