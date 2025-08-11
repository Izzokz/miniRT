/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_editor_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:42:37 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/11 18:48:48 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

inline char	not_numeric_free(char *const s)
{
	int	i;

	i = -1;
	while (*(s + ++i))
	{
		if (*(s + i) == '\n')
			break ;
		if (*(s + i) < '0' || *(s + i) > '9')
		{
			free(s);
			return (1);
		}
	}
	i = !i;
	free((void *)(i * (uintptr_t)s));
	return (i);
}
