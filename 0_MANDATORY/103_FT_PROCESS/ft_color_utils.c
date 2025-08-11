/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 15:22:03 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/11 22:24:18 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

inline void	ft_vec_offset(t_vec newv, const t_vec v1,
	const t_vec v2, const double epsilon)
{
	ft_new_vec(newv, v1[0] + v2[0] * epsilon, v1[1]
		+ v2[1] * epsilon, v1[2] + v2[2] * epsilon);
}

inline void	ft_vec_random_sphere(t_vec random, const t_vec lpos)
{
	double	percent;

	percent = (double)(ft_rand() % 101) / 100;
	random[0] = ((double)(ft_rand() % 201) - 100) / 100;
	random[1] = ((double)(ft_rand() % 201) - 100) / 100;
	random[2] = ((double)(ft_rand() % 201) - 100) / 100;
	ft_vec_scale(random, random, MRT_LIGHT_RADIUS * percent);
	ft_vec_add(random, lpos, random);
}

inline double	ft_get_lambert(const t_ray hit, const t_vec dir)
{
	t_ray	ray;
	double	dot;

	ft_new_ray(ray, hit[0], dir);
	dot = ft_vec_dot(hit[1], ray[1]);
	return (dot * (dot >= 0));
}

inline void	ft_store(t_ray cat[2], const t_ray r1, const t_ray r2)
{
	ft_memcpy(cat[0], r1, sizeof(t_ray));
	ft_memcpy(cat[1], r2, sizeof(t_ray));
}

inline void	ft_color_merge(t_color edit, const t_color ambient,
	const t_color diffuse, const t_color specular)
{
	ft_color_add(edit, ambient);
	ft_color_add(edit, diffuse);
	ft_color_add(edit, specular);
}
