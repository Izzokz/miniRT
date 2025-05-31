/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:25:46 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/05/31 18:25:48 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

inline void	ft_new_vec(t_vec newv, const double x,
	const double y, const double z)
{
	*newv = x;
	*(newv + 1) = y;
	*(newv + 2) = z;
}

inline void	ft_cpy_vec(t_vec newv, const t_vec cpy)
{
	ft_new_vec(newv, *cpy, *(cpy + 1), *(cpy + 2));
}
