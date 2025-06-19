/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_ads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:15:43 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/06/19 15:15:44 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

inline static void	ft_color_mult(t_color edit, const t_color m1,
	const t_color m2)
{
	*edit = *m1 * *m2;
	*(edit + 1) = *(m1 + 1) * *(m2 + 1);
	*(edit + 2) = *(m1 + 2) * *(m2 + 2);
}

void	ft_color_ads(t_color edit, const t_scene *scene,
	const t_obj *all, const int hit)
{
	t_color	ambient;
	t_color	diffuse[2];
	t_color	specular;
	t_ray	tmp;
	int		i;

	ft_color_mult(ambient, scene->color, (*(all + hit)).color);
	*diffuse = (t_color){0, 0, 0};
	i = -1;
	while ((*(all + ++i)).params)
	{
		if ((*(all + i)).type != 'l')
			continue ;
		ft_new_ray(tmp, *scene->ray, (t_vec){(*(*(all + i)).params),
			*((*(all + i)).params + 1), *((*(all + i)).params + 2)});
		ft_color_mult(*(diffuse + 1), (*(all + hit)).color, (*(all + i)).color);
		ft_color_mult(*(diffuse + 1), *(diffuse + 1),
			ft_pos_val(ft_vec_dot(*(scene->ray + 1), *(tmp + 1))));
		ft_color_add(*diffuse, *(diffuse + 1));
	}
	ft_color_scale(specular, (*(all + i)).color,
		ft_pow(ft_pos_val(ft_vec_dot(/*complete*/)),
			*((*(all + i)).params + 3)));
	edit = ambient + diffuse + specular;
}
