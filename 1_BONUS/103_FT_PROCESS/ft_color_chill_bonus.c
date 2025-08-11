/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_chill_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:15:43 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/11 18:35:19 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static inline void	ft_chill(t_color edit, const t_color origin,
	const float bfactor)
{
	static const t_color	chill = {207, 255, 249};
	t_vec					tmp;

	*tmp = (double)*origin / 255;
	*(tmp + 1) = (double)*(origin + 1) / 255;
	*(tmp + 2) = (double)*(origin + 2) / 255;
	*tmp = fmin(1.0, *tmp * .6 + .4 + .1 * sin(*(tmp + 1) * 5));
	*(tmp + 1) = fmin(1.0, *(tmp + 1) * .6 + .4 + .05 * cos(*tmp * 7));
	*(tmp + 2) = fmin(1.0, *(tmp + 2) * .6 + .4 + .1 * sin(*(tmp + 2) * 3));
	*edit = (1.0f - bfactor) * *origin
		+ bfactor * (.7 * *tmp * 255.0f + .3f * *chill);
	*(edit + 1) = (1.0f - bfactor) * *(origin + 1)
		+ bfactor * (.7 * *(tmp + 1) * 255.0f + .3f * *(chill + 1));
	*(edit + 2) = (1.0f - bfactor) * *(origin + 2)
		+ bfactor * (.7 * *(tmp + 2) * 255.0f + .3f * *(chill + 2));
}

unsigned int	ft_color_chill(t_ray hit_ray, t_obj *hit, t_scene *scene,
	const t_rules *rules)
{
	t_color	color;
	t_color	reflect;
	t_color	bounce;
	char	iter;

	ft_memset(color, 0, 3);
	ft_color_ads_bug(color, scene, hit);
	scene->mult = rules->ref_str;
	iter = -1;
	while (++iter < rules->ref)
	{
		hit = ft_hit_nearest_obj(hit_ray, scene->objects);
		if (!hit)
			break ;
		ft_memset(bounce, 0, 3);
		ft_color_ads_bug(bounce, scene, hit);
		ft_color_reflect(reflect, bounce, scene->mult);
		ft_color_add(color, reflect);
		scene->mult *= .75f;
	}
	ft_color_fix(color);
	ft_chill(color, color, .969);
	return (ft_convert_color(color));
}
