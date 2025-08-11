/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:26:09 by lumugot           #+#    #+#             */
/*   Updated: 2025/08/11 18:26:57 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	validate_ambient_light(char **tokens, t_scene *scene)
{
	scene->ambient_light.ratio = ft_atod(tokens[0]);
	if (scene->ambient_light.ratio < 0.0 || scene->ambient_light.ratio > 1.0)
	{
		print_error("Ambient light ratio must be in range [0.0,1.0]");
		return (PARSE_KO);
	}
	if (parse_color(tokens[1], scene->ambient_light.color) != PARSE_OK)
	{
		print_error("Invalid ambient light color");
		return (PARSE_KO);
	}
	scene->ambient_light.is_set = 1;
	return (PARSE_OK);
}

int	parse_ambient(char **tokens, t_scene *scene)
{
	if (scene->ambient_light.is_set)
	{
		print_error("Ambient light already set");
		return (PARSE_KO);
	}
	if (!tokens[0] || !tokens[1] || tokens[2])
	{
		print_error("Invalid ambient light format");
		return (PARSE_KO);
	}
	return (validate_ambient_light(tokens, scene));
}
