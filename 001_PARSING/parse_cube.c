/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cube.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 08:23:08 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/24 14:35:45 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline char	fill_cube(t_obj *new_obj, char **tokens)
{
	new_obj->params = malloc(sizeof(double) * 7);
	if (!new_obj->params)
	{
		free(new_obj);
		return (MALLOC_FAILED);
	}
	parse_vec3(*tokens, new_obj->params);
	parse_vec3(*(tokens + 1), new_obj->params + 3);
	if (new_obj->params[3] == 0 && new_obj->params[4] == 0
		&& new_obj->params[5] == 0)
	{
		print_error("Cube orientation vector cannot be null");
		free(new_obj->params);
		free(new_obj);
		return (PARSE_KO);
	}
	*(new_obj->params + 6) = ft_atod(*(tokens + 2));
	parse_color(*(tokens + 3), new_obj->color);
	new_obj->hit = ft_hit_c3;
	new_obj->next = NULL;
	return (PARSE_OK);
}

char	parse_cube(char **tokens, t_scene *scene)
{
	t_obj	*new_obj;

	if (!*tokens || !*(tokens + 1) || !*(tokens + 2) || !*(tokens + 3)
		|| *(tokens + 4))
	{
		print_error("Invalid cube format: "
			"c3 <pos x,y,z> <size> <color r,g,b>");
		return (PARSE_KO);
	}
	new_obj = malloc(sizeof(t_obj));
	if (!new_obj || fill_cube(new_obj, tokens) != PARSE_OK)
		return (MALLOC_FAILED);
	add_obj_to_scene(&scene->objects, new_obj);
	return (PARSE_OK);
}
