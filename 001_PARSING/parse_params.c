/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:39:47 by lumugot           #+#    #+#             */
/*   Updated: 2025/07/21 14:28:08 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

int	check_and_parse_vec3(char **components, t_vec vec)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (is_valid_params(components[i]) == PARSE_KO)
			return (PARSE_KO);
		i++;
	}
	vec[0] = ft_atod(components[0]);
	vec[1] = ft_atod(components[1]);
	vec[2] = ft_atod(components[2]);
	return (PARSE_OK);
}

int	parse_vec3(char *token, t_vec vec)
{
	char	**components;
	int		status;

	components = ft_split(token, ',');
	if (!components || !components[0] || !components[1] || !components[2]
		|| components[3])
	{
		free_tab(components);
		return (PARSE_KO);
	}
	status = check_and_parse_vec3(components, vec);
	free_tab(components);
	return (status);
}

int	check_and_parse_color(char **components, t_color color)
{
	int		i;
	double	tmp;

	i = 0;
	while (i < 3)
	{
		if (is_valid_params(components[i]) == PARSE_KO)
			return (PARSE_KO);
		tmp = ft_atod(components[i]);
		if (tmp < 0 || tmp > 255)
			return (PARSE_KO);
		color[i] = (unsigned char)tmp;
		i++;
	}
	return (PARSE_OK);
}

int	parse_color(char *token, t_color color)
{
	char	**components;
	int		status;

	components = ft_split(token, ',');
	if (!components || !components[0] || !components[1] || !components[2]
		|| components[3])
	{
		free_tab(components);
		return (PARSE_KO);
	}
	status = check_and_parse_color(components, color);
	free_tab(components);
	return (status);
}
