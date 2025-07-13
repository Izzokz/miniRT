/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:40:35 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/06/19 13:15:10 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

void	ft_ray_dir(t_ray ray, const t_vec target)
{
	ft_vec_sub(*(ray + 1), target, *ray);
	ft_vec_norm(*(ray + 1), *(ray + 1));
}

void	ft_new_ray(t_ray newr, const t_vec pos, const t_vec target)
{
	ft_cpy_vec(*newr, pos);
	ft_ray_dir(newr, target);
}

void	ft_cpy_ray(t_ray newr, const t_ray cpy)
{
	ft_cpy_vec(*newr, *cpy);
	ft_cpy_vec(*(newr + 1), *(cpy + 1));
}
