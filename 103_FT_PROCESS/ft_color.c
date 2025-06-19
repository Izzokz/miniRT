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

inline void	ft_color_scale(t_color edit, const float scale)
{
	*edit *= scale;
	*(edit + 1) *= scale;
	*(edit + 2) *= scale;
}

inline static void	ft_color_mult(t_color edit, const t_color m1,
	const t_color m2)
{
	*edit = *m1 * *m2;
	*(edit + 1) = *(m1 + 1) * *(m2 + 1);
	*(edit + 2) = *(m1 + 2) * *(m2 + 2);
}

inline void	ft_color_add(t_color edit, const t_color sum)
{
	*edit += *scale;
	*(edit + 1) += *(scale + 1);
	*(edit + 2) += *(scale + 2);
}

inline void	ft_color_reflect(t_color edit,
	const t_color base, const float multiplicator)
{
	*edit = (unsigned char)(*base * multiplicator);
	*(edit + 1) = (unsigned char)(*(base + 1) * multiplicator);
	*(edit + 2) = (unsigned char)(*(base + 2) * multiplicator);
}

void	ft_color_ads(t_color edit, const t_global *global,
	const t_obj *all, const int hit)
{
	t_color	ambient;
	t_color	diffuse[2];
	t_color	specular;
	t_ray	tmp;
	int		i;

	ft_color_mult(ambient, global->color, (*(all + hit)).color);
	*diffuse = (t_color){};
	i = -1;
	while ((*(all + ++i)).params)
	{
		if ((*(all + i)).type != 'l')
			continue;
		ft_new_ray(tmp, *global->ray, (t_vec){(*(all + i)).params});
		ft_color_mult(*(diffuse + 1), (*(all + hit)).color, (*(all + i)).color);
		ft_color_mult(*(diffuse + 1), *(diffuse + 1),
			ft_pos_val(ft_vec_dot(*(global->ray + 1), *(tmp + 1))));
		ft_color_add(*diffuse, *(diffuse + 1));
	}
	ft_color_scale(specular, (*(all + i)).color,
		ft_pow(ft_pos_val(ft_vec_dot(/*complete*/)), *((*(all + i)).params + 3)));
	edit = ambient + diffuse + specular;
}
