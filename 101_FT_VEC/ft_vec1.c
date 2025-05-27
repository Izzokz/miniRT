/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:34:31 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/05/26 14:34:34 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

inline float	ft_vec_dot(const t_vec v1, const t_vec v2)
{
	return ((*v1 * *v2) + (*(v1 + 1) * *(v2 + 1)) + (*(v1 + 2) * *(v2 + 2)));
}

inline float	ft_vec_mag(const t_vec v)
{
	return (sqrtf(ft_vec_dot(v, v)));
}

void	ft_vec_norm(t_vec *newv, const t_vec v)
{
	const float	mag = ft_vec_mag(v);

	if (mag > 0)
		ft_vec_div(newv, v, (t_vec){mag, mag, mag});
	else
		ft_cpy_vec(newv, (t_vec){.0f, .0f, .0f});
}

inline void	ft_cpy_vec(t_vec *newv, const t_vec cpy)
{
	**newv = *cpy;
	*(*newv + 1) = *(cpy + 1);
	*(*newv + 2) = *(cpy + 2);
}
