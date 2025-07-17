/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_c3_reflect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:05:55 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/15 10:05:56 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline double	ft_local_to_world(t_vec local, t_vec axes[3], char i)
{
	return (*local * *(*axes + i)
		+ *(local + 1) * *(*(axes + 1) + i)
		+ *(local + 2) * *(*(axes + 2) + i));
}

char	ft_c3_reflect(t_ray ray, t_ray local,
	t_vec axes_c3pos[4], double minhalf[2])
{
	t_vec	localpn[2];
	t_vec	posnorm[2];
	char	i;

	i = -1;
	while (++i < 3)
	{
		*(*localpn + i) = *(*local + i) + *minhalf * *(*(local + 1) + i);
		if (fabs(*(*localpn + i) - *(minhalf + 1)) < 1e-4)
			*(*(localpn + 1) + i) = 1.0;
		else if (fabs(*(*localpn + i) + *(minhalf + 1)) < 1e-4)
			*(*(localpn + 1) + i) = -1.0;
		else
			*(*(localpn + 1) + i) = 0.0;
		*(*posnorm + i) = *(*(axes_c3pos + 3) + i)
			+ ft_local_to_world(*localpn, axes_c3pos, i);
		*(*(posnorm + 1) + i) = ft_local_to_world(*(localpn + 1),
				axes_c3pos, i);
	}
	ft_vec_norm(*(posnorm + 1), *(posnorm + 1));
	ft_reflect(ray, posnorm);
	return (1);
}
