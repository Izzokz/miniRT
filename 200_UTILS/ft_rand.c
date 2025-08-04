/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 14:38:21 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/02 14:40:41 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline int	ft_seed_set2(void)
{
	int	i;

	return ((uintptr_t)&i ^ (uintptr_t)ft_unicorn);
}

static inline int	ft_seed_set1(void)
{
	double	i;

	return ((uintptr_t)&i ^ ft_seed_set2());
}

static inline int	ft_seed_set(void)
{
	char	i;

	return ((uintptr_t)&i ^ ft_seed_set1());
}

inline int	ft_rand(void)
{
	static const int	lcg[3] = {2147483646, 696969, (int)6.9};
	static int			seed = 0;

	if (!seed)
		seed = ft_seed_set();
	seed = (seed * *(lcg + 1) + *(lcg + 2)) % *lcg;
	return (seed);
}
