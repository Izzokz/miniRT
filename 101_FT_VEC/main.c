/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:06:41 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/06/19 13:14:59 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

/* ME SMASH HEAD */
void	msh(const t_vec pts[6], t_vec best_path_out[7])
{
	double	best_len = 9999999;
	int		best_path[7];

	for (int a = 1; a <= 5; ++a)
	for (int b = 1; b <= 5; ++b) if (b != a)
	for (int c = 1; c <= 5; ++c) if (c != a && c != b)
	for (int d = 1; d <= 5; ++d) if (d != a && d != b && d != c)
	for (int e = 1; e <= 5; ++e) if (e != a && e != b && e != c && e != d)
	{
		double len = 0;
		len += ft_vec_dist(pts[0], pts[a]);
		len += ft_vec_dist(pts[a], pts[b]);
		len += ft_vec_dist(pts[b], pts[c]);
		len += ft_vec_dist(pts[c], pts[d]);
		len += ft_vec_dist(pts[d], pts[e]);
		len += ft_vec_dist(pts[e], pts[0]);

		if (len < best_len)
		{
			best_len = len;
			best_path[0] = 0;
			best_path[1] = a;
			best_path[2] = b;
			best_path[3] = c;
			best_path[4] = d;
			best_path[5] = e;
			best_path[6] = 0;
		}
	}

	for (int i = 0; i < 7; ++i)
		ft_cpy_vec(*(best_path_out + i), *(pts + *(best_path + i)));
}

static inline void	print_vec(const t_vec v)
{
	printf("{%lf, %lf, %lf}", *v, *(v + 1), *(v + 2));
}

int	main(void)
{
	t_vec	all[6]; // nucleus, goblin, divan, remnants, bal, temple
	t_vec	best[7]; // processed run

	ft_new_vec(*all, 500, 150, 500);
	ft_new_vec(*(all + 1), 1000, 110, 500);
	ft_new_vec(*(all + 2), 632, 80, 867);
	ft_new_vec(*(all + 3), 95, 135, 874);
	ft_new_vec(*(all + 4), 235, 76, 199);
	ft_new_vec(*(all + 5), 735, 96, 250);
	msh(all, best);
	for (char i = 0; i < 7; i++)
	{
		printf("[%d]\t", i);
		print_vec(*(best + i));
		printf("\n");
	}

	t_obj	*allo;
	t_ray	ray;
	int		i;
	ft_init_obj(2);
	i = -1;
	ft_make_p((t_vec [2]){{0, -5, 10}, {0, 1, 0}}, (t_color){255, 255, 255});
	ft_make_p((t_vec [2]){{0, 5, 10}, {0, -1, 0}}, (t_color){255, 255, 255});
	allo = ft_get_obj();
	printf("PLANE NORMALS :\n");
	print_vec((t_vec){*(allo->params + 3), *(allo->params + 4), *(allo->params + 5)});
	printf("\n");
	print_vec((t_vec){*((allo + 1)->params + 3), *((allo + 1)->params + 4), *((allo + 1)->params + 5)});
	ft_new_ray(ray, (t_vec){0, 0, 0}, (t_vec){0, -5, 10});
	printf("\nBEFORE FIRST HIT :\n");
	print_vec(*ray);
	print_vec(*(ray + 1));
	for (char i = 1; i < 11; ++i)
	{
		allo->hit(*allo, ray);
		printf("\nAFTER HIT FLOOR %d :\n", i);
		print_vec(*ray);
		print_vec(*(ray + 1));
		(allo + 1)->hit(*(allo + 1), ray);
		printf("\nAFTER HIT CEILING %d :\n", i);
		print_vec(*ray);
		print_vec(*(ray + 1));
	}
	ft_free_obj();
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
