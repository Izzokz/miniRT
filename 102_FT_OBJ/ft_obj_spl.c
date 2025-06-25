/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_spl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:37:22 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/06/25 14:16:25 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

void	ft_reflect(t_ray ray, const t_vec posnorm[2])
{
	double	dot;
	t_vec	tmp;

	dot = 2.0 * ft_vec_dot(*(ray + 1), *(posnorm + 1));
	ft_vec_scale(tmp, *(posnorm + 1), dot);
	ft_cpy_vec(*ray, *posnorm);
	ft_vec_sub(*(ray + 1), *(ray + 1), tmp);
}

/*
abdt = A, B, Delta, t
*/
char	ft_hit_s(const t_obj sphere, t_ray ray)
{
	double	abdt[4];
	t_vec	tmp[2];

	ft_cpy_vec(*(tmp + 1), (t_vec){(*sphere.params),
		*(sphere.params + 1), *(sphere.params + 2)});
	ft_vec_sub(*tmp, *ray, *(tmp + 1));
	*abdt = ft_vec_dot(*(ray + 1), *(ray + 1));
	*(abdt + 1) = 2.0 * ft_vec_dot(*tmp, *(ray + 1));
	*(abdt + 2) = (*(abdt + 1) * *(abdt + 1))
		- 4.0 * *abdt * (ft_vec_dot(*tmp, *tmp)
			- ((*(sphere.params + 3) / 2) * (*(sphere.params + 3) / 2)));
	if (*(abdt + 2) < 0)
		return (0);
	*(abdt + 3) = (-*(abdt + 1) - sqrt(*(abdt + 2))) / (2.0 * *abdt);
	if (*(abdt + 3) < 0)
		*(abdt + 3) = (-*(abdt + 1) + sqrt(*(abdt + 2))) / (2.0 * *abdt);
	if (*(abdt + 3) < 0)
		return (0);
	ft_vec_scale(*tmp, *(ray + 1), *(abdt + 3));
	ft_vec_add(*tmp, *ray, *tmp);
	ft_vec_sub(*(tmp + 1), *tmp, *(tmp + 1));
	ft_vec_norm(*(tmp + 1), *(tmp + 1));
	ft_reflect(ray, tmp);
	return (1);
}

char	ft_hit_p(const t_obj pyramid, t_ray ray)
{
	(void) pyramid;
	(void) ray;
	return (0);
}

char	ft_hit_l(const t_obj light, t_ray ray)
{
	(void) light;
	(void) ray;
	return (0);
}
