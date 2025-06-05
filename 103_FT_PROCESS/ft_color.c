/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:15:46 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/06/05 14:15:47 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_process.h"

void	ft_color_scale(t_color edit, const t_color scale)
{
	*edit *= *scale;
	*(edit + 1) *= *(scale + 1);
	*(edit + 2) *= *(scale + 2);
}

void	ft_color_add(t_color edit, const t_color sum)
{
	*edit += *scale;
	*(edit + 1) += *(scale + 1);
	*(edit + 2) += *(scale + 2);
}

void	ft_color_reflect(t_color edit, const t_color base, float multiplicator)
{
	*edit = (unsigned char)(*base * multiplicator);
	*(edit + 1) = (unsigned char)(*(base + 1) * multiplicator);
	*(edit + 2) = (unsigned char)(*(base + 2) * multiplicator);
}
