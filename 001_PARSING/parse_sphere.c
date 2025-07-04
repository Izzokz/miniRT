/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:35:20 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/26 14:43:34 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

int	create_and_fill_sphere(t_obj **new_obj, char **tokens)
{
	*new_obj = malloc(sizeof(t_obj));
	if (!*new_obj)
		return (MALLOC_FAILED);
	ft_memset(*new_obj, 0, sizeof(t_obj));
	(*new_obj)->type = 's';
	(*new_obj)->params = malloc(sizeof(double) * 4);
	if (!(*new_obj)->params)
	{
		free(*new_obj);
		return (MALLOC_FAILED);
	}
	parse_vec3(tokens[1], (*new_obj)->params);
	(*new_obj)->params[3] = ft_atod(tokens[2]);
	parse_color(tokens[3], (*new_obj)->color);
	(*new_obj)->hit = ft_hit_s;
	(*new_obj)->next = NULL;
	return (PARSE_OK);
}

int	parse_sphere(char **tokens, t_scene *scene)
{
	t_obj	*new_obj;

	if (ft_strncmp(tokens[0], "sp", 3) != 0 || !tokens[1] || !tokens[2]
		|| !tokens[3])
	{
		print_error("Invalid sphere format: "
			"sp <pos x,y,z> <diameter> <color r,g,b>");
		return (PARSE_KO);
	}
	if (create_and_fill_sphere(&new_obj, tokens) != PARSE_OK)
		return (MALLOC_FAILED);
	add_obj_to_scene(&scene->objects, new_obj);
	return (PARSE_OK);
}
