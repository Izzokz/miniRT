/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:34:19 by lumugot           #+#    #+#             */
/*   Updated: 2025/08/01 19:18:09 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_light(char **tokens, t_scene *scene)
{
	if (scene->light.is_set)
	{
		print_error("Light already set");
		return (PARSE_KO);
	}
	if (!tokens[0] || !tokens[1] || tokens[2])
	{
		print_error("Invalid light format: "
			"L <pos x,y,z> <ratio>");
		return (PARSE_KO);
	}
	if (parse_vec3(tokens[0], scene->light.pos) != PARSE_OK)
	{
		print_error("Invalid light position format");
		return (PARSE_KO);
	}
	scene->light.brightness = ft_atod(tokens[1]);
	if (scene->light.brightness < 0.0 || scene->light.brightness > 1.0)
	{
		print_error("Light brightness ratio must be in range [0.0,1.0]");
		return (PARSE_KO);
	}
	scene->light.is_set = 1;
	return (PARSE_OK);
}
