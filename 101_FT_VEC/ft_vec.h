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

typedef float	t_vec[3];

void	ft_new_vec(t_vec *newv, const float x, const float y, const float z);
void	ft_cpy_vec(t_vec *newv, const t_vec cpy);

void	ft_vec_add(t_vec *newv, const t_vec v1, const t_vec v2);
void	ft_vec_sub(t_vec *newv, const t_vec v1, const t_vec v2);
void	ft_vec_scale(t_vec *newv, const t_vec v1, const t_vec v2);
void	ft_vec_div(t_vec *newv, const t_vec v1, const t_vec v2);

float	ft_vec_dot(const t_vec v1, const t_vec v2);
float	ft_vec_mag(const t_vec v);
void	ft_vec_norm(t_vec *newv, const t_vec v);

#endif
