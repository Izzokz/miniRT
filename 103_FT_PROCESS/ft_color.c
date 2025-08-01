/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:15:46 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/01 11:32:55 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

inline void	ft_color_mult(t_color edit, const t_color m1,
	const t_color m2)
{
	unsigned int	greater_color[3];

	*greater_color = *m1 * ((float)*m2 / 255);
	*(greater_color + 1) = *(m1 + 1) * ((float)*(m2 + 1) / 255);
	*(greater_color + 2) = *(m1 + 2) * ((float)*(m2 + 2) / 255);
	if (*greater_color > 255)
		*edit = 255;
	else
		*edit = *greater_color;
	if (*(greater_color + 1) > 255)
		*(edit + 1) = 255;
	else
		*(edit + 1) = *(greater_color + 1);
	if (*(greater_color + 2) > 255)
		*(edit + 2) = 255;
	else
		*(edit + 2) = *(greater_color + 2);
}

inline void	ft_color_scale(t_color edit, const float scale)
{
	unsigned int	greater_color[3];

	*greater_color = *edit * scale;
	*(greater_color + 1) = *(edit + 1) * scale;
	*(greater_color + 2) = *(edit + 2) * scale;
	if (*greater_color > 255)
		*edit = 255;
	else
		*edit = *greater_color;
	if (*(greater_color + 1) > 255)
		*(edit + 1) = 255;
	else
		*(edit + 1) = *(greater_color + 1);
	if (*(greater_color + 2) > 255)
		*(edit + 2) = 255;
	else
		*(edit + 2) = *(greater_color + 2);
}

inline void	ft_color_add(t_color edit, const t_color sum)
{
	unsigned int	greater_color[3];

	*greater_color = *edit + *sum;
	*(greater_color + 1) = *(edit + 1) + *(sum + 1);
	*(greater_color + 2) = *(edit + 2) + *(sum + 2);
	if (*greater_color > 255)
		*edit = 255;
	else
		*edit = *greater_color;
	if (*(greater_color + 1) > 255)
		*(edit + 1) = 255;
	else
		*(edit + 1) = *(greater_color + 1);
	if (*(greater_color + 2) > 255)
		*(edit + 2) = 255;
	else
		*(edit + 2) = *(greater_color + 2);
}

inline void	ft_color_reflect(t_color edit,
	const t_color base, const float multiplicator)
{
	unsigned int	greater_color[3];

	*greater_color = *base * multiplicator;
	*(greater_color + 1) = *(base + 1) * multiplicator;
	*(greater_color + 2) = *(base + 2) * multiplicator;
	if (*greater_color > 255)
		*edit = 255;
	else
		*edit = *greater_color;
	if (*(greater_color + 1) > 255)
		*(edit + 1) = 255;
	else
		*(edit + 1) = *(greater_color + 1);
	if (*(greater_color + 2) > 255)
		*(edit + 2) = 255;
	else
		*(edit + 2) = *(greater_color + 2);
}

inline unsigned int	ft_convert_color(const t_color color)
{
	return (color[0] << 16 | color[1] << 8 | color[2]);
}
