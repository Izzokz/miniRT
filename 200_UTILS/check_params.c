/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 12:12:50 by lumugot           #+#    #+#             */
/*   Updated: 2025/07/21 12:18:17 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

int	is_valid_params(const char *str)
{
	int	index;
	int	count_dot;

	index = 0;
	count_dot = 0;
	if (!str || !str[0])
		return (PARSE_KO);
	if (str[index] == '+' || str[index] == '-')
		index++;
	if (!str[index])
		return (PARSE_KO);
	while (str[index])
	{
		if(str[index] == '.')
			count_dot++;
		else if (!ft_isdigit(str[index]))
			return (PARSE_KO);
		index++;
	}
	if (count_dot > 1)
		return (PARSE_KO);
	return (PARSE_OK);
}
