/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_spl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:37:22 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/05/29 15:37:23 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_obj.h"

char	ft_make_spl(const char type, const t_vec pos,
	const double attr, const t_color color)
{
	t_obj	*newobj;

	newobj = ft_get_uninit_obj();
	newobj->params = malloc(sizeof(double) * 4);
	if (!newobj->params)
		return (-1);
	ft_memcpy((void *)newobj->params,
		(double [4]){*pos, *(pos + 1), *(pos + 2), attr},
		sizeof(double) * 4);
	newobj->type = type;
	ft_memcpy(newobj->color, color, 3);
	newobj->hit = ft_hit_l;
	if (type == 's')
		newobj->hit = ft_hit_s;
	else if (type == 'p')
		newobj->hit = ft_hit_l;
	return (0);
}

void	ft_reflect(t_ray ray, const t_vec posnorm[2])
{
	double	dot;
	t_vec	tmp;

	dot = 2.0 * ft_vec_dot(*(ray + 1), *(posnorm + 1));
	ft_vec_scale(tmp, *(posnorm + 1), dot);
	ft_cpy_vec(*ray, *posnorm);
	ft_vec_sub(*(ray + 1), *(ray + 1), tmp);
}

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
			- (*(sphere.params + 3) * *(sphere.params + 3)));
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
