/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:36:28 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/26 14:43:52 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

int	create_and_fill_plane(t_obj **new_obj, char **tokens)
{
	*new_obj = malloc(sizeof(t_obj));
	if (!*new_obj)
		return (MALLOC_FAILED);
	ft_memset(*new_obj, 0, sizeof(t_obj));
	(*new_obj)->type = 'p';
	(*new_obj)->params = malloc(sizeof(double) * 6);
	if (!(*new_obj)->params)
	{
		free(*new_obj);
		return (MALLOC_FAILED);
	}
	parse_vec3(tokens[1], (*new_obj)->params);
	parse_vec3(tokens[2], (*new_obj)->params + 3);
	parse_color(tokens[3], (*new_obj)->color);
	(*new_obj)->next = NULL;
	return (PARSE_OK);
}

int	parse_plane(char **tokens, t_scene *scene)
{
	t_obj	*new_obj;

	if (ft_strncmp(tokens[0], "pl", 3) != 0 || !tokens[1] || !tokens[2]
		|| !tokens[3])
	{
		print_error("Invalid plane format: "
			"pl <pos x,y,z> <normal a,b,c> <color r,g,b>");
		return (PARSE_KO);
	}
	if (create_and_fill_plane(&new_obj, tokens) != PARSE_OK)
		return (MALLOC_FAILED);
	add_obj_to_scene(&scene->objects, new_obj);
	return (PARSE_OK);
}
