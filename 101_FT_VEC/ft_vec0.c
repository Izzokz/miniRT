/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:29:51 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/05/26 14:32:14 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

inline void	ft_vec_add(t_vec newv, const t_vec v1, const t_vec v2)
{
	ft_new_vec(newv, (*v1 + *v2), *(v1 + 1) + *(v2 + 1),
		*(v1 + 2) + *(v2 + 2));
}

inline void	ft_vec_sub(t_vec newv, const t_vec v1, const t_vec v2)
{
	ft_new_vec(newv, (*v1 - *v2), *(v1 + 1) - *(v2 + 1),
		*(v1 + 2) - *(v2 + 2));
}

inline void	ft_vec_scale(t_vec newv, const t_vec v, const double mult)
{
	ft_new_vec(newv, (*v * mult), *(v + 1) * mult,
		*(v + 2) * mult);
}

inline void	ft_vec_div(t_vec newv, const t_vec v, const double div)
{
	ft_new_vec(newv, (*v / div), *(v + 1) / div,
		*(v + 2) / div);
}
