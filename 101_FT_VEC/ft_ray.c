/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:40:35 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/05/27 17:40:38 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"

void	ft_ray_dir(t_ray ray, const t_vec target)
{
	t_vec	tmp;

	ft_vec_sub(&tmp, target, *ray);
	ft_vec_norm(ray + 1, tmp);
}

void	ft_new_ray(t_ray newr, const t_vec pos, const t_vec target)
{
	ft_cpy_vec(newr, pos);
	ft_ray_dir(newr, target);
}
