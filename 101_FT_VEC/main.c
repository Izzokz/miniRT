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

int	main(void)
{
	t_vec	a;
	t_vec	b;
	t_vec	*c;
	t_vec	d;

	ft_new_vec(&a, 1.66f, 1.5f, 0.1f);
	printf("{x: %f, y: %f, z: %f}\n", *a, *(a + 1), *(a + 2));
	ft_cpy_vec(&b, a);
	c = malloc(sizeof(t_vec));
	if (!c)
		return (1);
	ft_vec_add(c, a, b);
	printf("{x: %f, y: %f, z: %f}\n", **c, *(*c + 1), *(*c + 2));
	ft_vec_scale(&d, *c, (t_vec){5.551f, 6.1265f, 2.3f});
	printf("{x: %f, y: %f, z: %f}\n", *d, *(d + 1), *(d + 2));
	ft_vec_sub(&d, d, (t_vec){.5f, .1f, 3.3f});
	printf("{x: %f, y: %f, z: %f}\n", *d, *(d + 1), *(d + 2));
	ft_cpy_vec(&d, (t_vec){.1f, .1f, .1f});
	ft_vec_div(&d, d, d);
	printf("{x: %f, y: %f, z: %f}\n", *d, *(d + 1), *(d + 2));
	ft_vec_div(&d, d, (t_vec){.0f, .0f, .0f});
	printf("{x: %f, y: %f, z: %f}\n", *d, *(d + 1), *(d + 2));
	printf("MAG: %f\nDOT: %f\n", ft_vec_mag(a), ft_vec_dot(a, *c));
	ft_vec_norm(&d, a);
	printf("{x: %f, y: %f, z: %f}\n", *d, *(d + 1), *(d + 2));
	free(c);
	return (0);
}
