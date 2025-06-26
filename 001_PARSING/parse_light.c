/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:34:19 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/26 18:19:24 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

int	fill_light_data(t_light *light, char **tokens)
{
	if (parse_vec3(tokens[1], light->pos) != PARSE_OK)
	{
		print_error("Invalid light position format");
		return (PARSE_KO);
	}
	light->brightness = ft_atod(tokens[2]);
	if (light->brightness < 0.0 || light->brightness > 1.0)
	{
		print_error("Light brightness ratio must be in range [0.0,1.0]");
		return (PARSE_KO);
	}
	if (parse_color(tokens[3], light->color) != PARSE_OK)
	{
		print_error("Invalid light color");
		return (PARSE_KO);
	}
	return (PARSE_OK);
}

int	parse_light(char **tokens, t_scene *scene)
{
	t_light	*light;
	t_list	*new_node;

	if (ft_strncmp(tokens[0], "L", 2) != 0 || !tokens[1] || !tokens[2]
		|| !tokens[3])
	{
		print_error(L_ERROR);
		return (PARSE_KO);
	}
	light = malloc(sizeof(t_light));
	if (!light)
		return (MALLOC_FAILED);
	if (fill_light_data(light, tokens) != PARSE_OK)
	{
		free(light);
		return (PARSE_KO);
	}
	new_node = ft_lstnew(light);
	if (!new_node)
	{
		free(light);
		return (MALLOC_FAILED);
	}
	ft_lstadd_back(&scene->lights, new_node);
	return (PARSE_OK);
}
