/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:55:02 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/19 16:58:21 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

inline int	ft_isspace(int c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

inline void	skip_space(char *str)
{
	int	index;

	index = 0;
	while (str[index] && ft_isspace(str[index]))
		index++;
}
