/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:40:23 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/11 22:33:28 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OBJ_H
# define FT_OBJ_H

# include "typedef.h"

/* OBJ METHODS */
void	ft_reflect(t_ray, t_vec posnorm[2]);
char	ft_hit_s(const t_obj *sphere, t_ray ray);
char	ft_hit_c(const t_obj *cylinder, t_ray ray);
char	ft_hit_p(const t_obj *plane, t_ray ray);
char	ft_hit_cone(const t_obj *cone, t_ray ray);

/* OBJ FREE FUNCTION */
void	ft_free_obj(t_obj *head);

// cylinder's files
int		is_inside_cylinder(const t_obj *cy, t_vec point, t_vec axis);
double	solve_cylinder_quadratic_outside(double a, double b, double c);
double	solve_cylinder_quadratic_inside(double a, double b, double c);
double	intersect_body_outside(const t_obj *cy, t_ray ray, t_vec axis);
double	intersect_body_inside(const t_obj *cy, t_ray ray, t_vec axis);
double	cap_intersection(const t_obj *cy, t_ray ray, t_vec axis,
			int upper);
double	intersect_caps(const t_obj *cy, t_ray ray, t_vec axis);

#endif
