/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_mini.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:13:41 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/07 14:13:44 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

inline unsigned int	ft_color_mini(t_ray ray, t_obj *hit, t_scene *scene,
	const t_rules *rules)
{
	(void) ray;
	(void) scene;
	(void) rules;
	return (ft_convert_color(hit->color));
}
