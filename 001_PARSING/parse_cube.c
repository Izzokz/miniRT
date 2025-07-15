/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cube.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 08:23:08 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/15 08:23:09 by kzhen-cl         ###   ########.fr       */
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
	*(new_obj->params + 6) = ft_atod(*(tokens + 2));
	parse_color(*(tokens + 3), new_obj->color);
	new_obj->hit = ft_hit_c3;
	new_obj->next = NULL;
	return (PARSE_OK);
}

char	parse_cube(char **tokens, t_scene *scene)
{
	t_obj	*new_obj;

	if (!*tokens || !*(tokens + 1) || !*(tokens + 2) || !*(tokens + 3))
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
