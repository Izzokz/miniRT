/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:40:35 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/26 13:04:12 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_ray_dir(t_ray ray, const t_vec target)
{
	ft_vec_sub(ray[1], target, ray[0]);
	ft_vec_norm(ray[1], ray[1]);
}

void	ft_new_ray(t_ray newr, const t_vec pos, const t_vec target)
{
	ft_cpy_vec(newr[0], pos);
	ft_ray_dir(newr, target);
}

void	ft_cpy_ray(t_ray newr, const t_ray cpy)
{
	ft_cpy_vec(newr[0], cpy[0]);
	ft_cpy_vec(newr[1], cpy[1]);
}
