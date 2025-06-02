/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:06:41 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/05/26 15:06:42 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vec.h"
#include <stdio.h>
#include <stdlib.h>

static inline void	print_vec(const t_vec v)
{
	printf("{%lf, %lf, %lf}", *v, *(v + 1), *(v + 2));
}

int	main(void)
{
	t_vec		all[6]; //nucleus, goblin, divan, remnants, bal, temple
	char		i;
	char		j;
	double		tmp;
	double		closest_dist;

	ft_new_vec(*all, 500, 150, 500);
	ft_new_vec(*(all + 1), 655, 110, 300);
	ft_new_vec(*(all + 2), -315, 80, 216);
	ft_new_vec(*(all + 3), 466, 135, -500);
	ft_new_vec(*(all + 4), 200, 76, -566);
	ft_new_vec(*(all + 5), 220, 96, -666);
	closest_dist = 9999;
	i = -1;
	while (++i < 6)
	{
		j = -1;
		while (++j < 6)
		{
			if (j <= i)
				continue ;
			tmp = ft_vec_dist(*(all + i), *(all + j));
			print_vec(*(all + i));
			printf(" <-> ");
			print_vec(*(all + j));
			printf(" : %lf\n", tmp);
			if (tmp < closest_dist)
			{
				printf("Found closer distance ");
				print_vec(*(all + i));
				printf(" <-> ");
				print_vec(*(all + j));
				printf(" : %lf\n", tmp);
				closest_dist = tmp;
			}
		}
	}
	printf("Closest distance : %lf\n", closest_dist);
	return (0);
/*
	t_vec	a;
	t_vec	b;
	t_vec	*c;
	t_vec	d;
	t_ray	ray;
	t_ray	anotheray;
	t_vec	tmp;

	ft_new_vec(a, 1.66f, 1.5f, 0.1f);
	printf("{x: %lf, y: %lf, z: %lf}\n", *a, *(a + 1), *(a + 2));
	ft_cpy_vec(b, a);
	c = malloc(sizeof(t_vec));
	if (!c)
		return (1);
	ft_vec_add(*c, a, b);
	printf("{x: %lf, y: %lf, z: %lf}\n", **c, *(*c + 1), *(*c + 2));
	ft_vec_scale(d, *c, (t_vec){5.551f, 6.1265f, 2.3f});
	printf("{x: %lf, y: %lf, z: %lf}\n", *d, *(d + 1), *(d + 2));
	ft_vec_sub(d, d, (t_vec){.5f, .1f, 3.3f});
	printf("{x: %lf, y: %lf, z: %lf}\n", *d, *(d + 1), *(d + 2));
	ft_cpy_vec(d, (t_vec){.1f, .1f, .1f});
	ft_vec_div(d, d, d);
	printf("{x: %lf, y: %lf, z: %lf}\n", *d, *(d + 1), *(d + 2));
	ft_vec_div(d, d, (t_vec){.0f, .0f, .0f});
	printf("{x: %lf, y: %lf, z: %lf}\n", *d, *(d + 1), *(d + 2));
	printf("MAG: %lf\nDOT: %lf\n", ft_vec_mag(a), ft_vec_dot(a, *c));
	ft_vec_norm(d, a);
	printf("{x: %lf, y: %lf, z: %lf}\n", *d, *(d + 1), *(d + 2));
	ft_new_vec(*ray, .1f, .1f, .1f);
	ft_vec_sub(tmp, (t_vec){1.f, 1.f, 1.f}, *ray);
	ft_vec_norm(*(ray + 1), tmp);
	printf("LOC: {%lf, %lf, %lf}, DIR: {%lf, %lf, %lf}\n", **ray, *(*ray + 1), *(*ray + 2), *(*(ray + 1)), *(*(ray + 1) + 1), *(*(ray + 1) + 2));
	ft_new_ray(anotheray, (t_vec){.1f, .1f, .1f}, (t_vec){1.f, 1.f, 1.f});
	printf("LOC: {%lf, %lf, %lf}, DIR: {%lf, %lf, %lf}\n", **anotheray, *(*anotheray + 1), *(*anotheray + 2), *(*(anotheray + 1)), *(*(anotheray + 1) + 1), *(*(anotheray + 1) + 2));
	ft_cpy_vec(*anotheray, (t_vec){5.3f, 2.6f, 9.6635f});
	ft_ray_dir(anotheray, (t_vec){1.2f, 3.3f, -.2f});
	printf("LOC: {%lf, %lf, %lf}, DIR: {%lf, %lf, %lf}\n", **anotheray, *(*anotheray + 1), *(*anotheray + 2), *(*(anotheray + 1)), *(*(anotheray + 1) + 1), *(*(anotheray + 1) + 2));
	free(c);
	printf("Distance between a and d : %lf\n", ft_vec_dist(a, d));
	printf("Distance between d and a : %lf\n", ft_vec_dist(d, a));
	return (0);
*/
}
