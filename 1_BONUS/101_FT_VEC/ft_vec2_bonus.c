/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:25:46 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/11 18:30:25 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

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
