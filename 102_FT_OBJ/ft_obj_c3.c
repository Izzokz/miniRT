/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_c3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:08:49 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/15 10:08:50 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline void	ft_get_rot_axes(t_vec axes[3], const t_vec orientation)
{
	if (fabs(*(orientation + 1)) < .99)
		ft_vec_cross(*axes, g_up, orientation);
	else
		ft_vec_cross(*axes, g_right, orientation);
	ft_vec_norm(*axes, *axes);
	ft_vec_cross(*(axes + 1), orientation, *axes);
	ft_vec_norm(*(axes + 1), *(axes + 1));
	ft_cpy_vec(*(axes + 2), orientation);
}

static inline void	ft_make_local_ray(t_ray local, const t_ray ray,
	const t_vec center, const t_vec axes[3])
{
	t_vec	tmp;
	char	i;

	ft_vec_sub(tmp, *ray, center);
	i = -1;
	while (++i < 3)
	{
		*(*local + i) = ft_vec_dot(tmp, *(axes + i));
		*(*(local + 1) + i) = ft_vec_dot(*(ray + 1), *(axes + i));
	}
}

static inline char	ft_c3_does_hit2(double t0t1minmax[4])
{
	if (*t0t1minmax > *(t0t1minmax + 1))
		ft_swap(t0t1minmax, t0t1minmax + 1);
	if (*t0t1minmax > *(t0t1minmax + 2))
		*(t0t1minmax + 2) = *t0t1minmax;
	if (*(t0t1minmax + 1) < *(t0t1minmax + 3))
		*(t0t1minmax + 3) = *(t0t1minmax + 1);
	return (*(t0t1minmax + 2) < *(t0t1minmax + 3));
}

static inline char	ft_c3_does_hit(double half, t_ray local, double *min)
{
	double	t0t1minmax[4];
	double	od[2];
	char	i;

	*(t0t1minmax + 2) = -INFINITY;
	*(t0t1minmax + 3) = INFINITY;
	i = -1;
	while (++i < 3)
	{
		*od = *(*local + i);
		*(od + 1) = *(*(local + 1) + i);
		if (fabs(*(od + 1)) < 1e-6)
		{
			if (fabs(*od) > half)
				return (0);
			continue ;
		}
		*t0t1minmax = (-half - *od) / *(od + 1);
		*(t0t1minmax + 1) = (half - *od) / *(od + 1);
		if (!ft_c3_does_hit2(t0t1minmax))
			return (0);
	}
	*min = *(t0t1minmax + 2);
	return (*(t0t1minmax + 3) >= 0);
}

char	ft_hit_c3(const t_obj *cube, t_ray ray)
{
	t_vec	axes_c3pos[4];
	double	minhalf[2];
	t_ray	local;

	ft_get_rot_axes(axes_c3pos, cube->params + 3);
	ft_make_local_ray(local, ray, cube->params, axes_c3pos);
	*(minhalf + 1) = *(cube->params + 6) / 2;
	if (ft_c3_does_hit(*(minhalf + 1), local, minhalf))
	{
		ft_cpy_vec(*(axes_c3pos + 3), cube->params);
		return (ft_c3_reflect(ray, local, axes_c3pos, minhalf));
	}
	return (0);
}
