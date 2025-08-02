/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:34:31 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/02 16:13:03 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

inline double	ft_vec_dot(const t_vec v1, const t_vec v2)
{
	return (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]);
}

inline double	ft_vec_mag(const t_vec v)
{
	return (sqrt(ft_vec_dot(v, v)));
}

void	ft_vec_norm(t_vec newv, const t_vec v)
{
	const double	mag = ft_vec_mag(v);

	if (mag > 0)
		ft_vec_div(newv, v, mag);
	else
		ft_new_vec(newv, .0f, .0f, .0f);
}

void	ft_vec_neg(t_vec newv, const t_vec v)
{
	ft_new_vec(newv, -v[0], -v[1], -v[2]);
}

inline double	ft_vec_dist(const t_vec v1, const t_vec v2)
{
	return (sqrt(((v2[0] - v1[0]) * (v2[0] - v1[0]))
			+ ((v2[1] - v1[1]) * (v2[1] - v1[1]))
			+ ((v2[2] - v1[2]) * (v2[2] - v1[2]))));
}
