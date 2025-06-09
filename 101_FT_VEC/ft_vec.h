/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:17:39 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/05/26 14:18:53 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VEC_H
# define FT_VEC_H

# include <math.h>

typedef double	t_vec[3]; // x, y, z
typedef t_vec	t_ray[2]; // pos, dir

/* VEC SETTER */
void	ft_new_vec(t_vec newv, const double x, const double y, const double z);
void	ft_cpy_vec(t_vec newv, const t_vec cpy);

/* VEC ARITHMETICS */
void	ft_vec_add(t_vec newv, const t_vec v1, const t_vec v2);
void	ft_vec_sub(t_vec newv, const t_vec v1, const t_vec v2);
void	ft_vec_scale(t_vec newv, const t_vec v, const double mult);
void	ft_vec_div(t_vec newv, const t_vec v, const double div);

/* VEC ALGEBRA */
double	ft_vec_dot(const t_vec v1, const t_vec v2);
double	ft_vec_mag(const t_vec v);
double	ft_vec_dist(const t_vec v1, const t_vec v2);
void	ft_vec_norm(t_vec newv, const t_vec v);
void	ft_vec_neg(t_vec newv, const t_vec v);

/* RAY SETTER */
void	ft_new_ray(t_ray newr, const t_vec pos, const t_vec target);
void	ft_cpy_ray(t_ray newr, const t_ray cpy);
void	ft_ray_dir(t_ray ray, const t_vec target);

#endif
