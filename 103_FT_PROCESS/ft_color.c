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

#include "miniRT.h"

inline void	ft_color_scale(t_color edit, const float scale)
{
	*edit *= scale;
	*(edit + 1) *= scale;
	*(edit + 2) *= scale;
}

inline void	ft_color_add(t_color edit, const t_color sum)
{
	*edit += *sum;
	*(edit + 1) += *(sum + 1);
	*(edit + 2) += *(sum + 2);
}

inline void	ft_color_reflect(t_color edit,
	const t_color base, const float multiplicator)
{
	*edit = (unsigned char)(*base * multiplicator);
	*(edit + 1) = (unsigned char)(*(base + 1) * multiplicator);
	*(edit + 2) = (unsigned char)(*(base + 2) * multiplicator);
}
