/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:25:46 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/26 13:04:03 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

inline void	ft_new_vec(t_vec newv, const double x,
	const double y, const double z)
{
	newv[0] = x;
	newv[1] = y;
	newv[2] = z;
}

inline void	ft_cpy_vec(t_vec newv, const t_vec cpy)
{
	ft_new_vec(newv, cpy[0], cpy[1], cpy[2]);
}
