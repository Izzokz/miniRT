/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:11:25 by lumugot           #+#    #+#             */
/*   Updated: 2025/07/04 13:14:55 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

void	add_obj_to_scene(t_obj **objects, t_obj *new_obj)
{
	if (!*objects)
	{
		*objects = new_obj;
		return ;
	}
	add_obj_to_scene(&(*objects)->next, new_obj);
}

int	create_and_fill_cylinder(t_obj **new_obj, char **tokens)
{
	*new_obj = malloc(sizeof(t_obj));
	if (!*new_obj)
		return (MALLOC_FAILED);
	ft_memset(*new_obj, 0, sizeof(t_obj));
	(*new_obj)->type = 'c';
	(*new_obj)->params = malloc(sizeof(double) * 8);
	if (!(*new_obj)->params)
	{
		free(*new_obj);
		return (MALLOC_FAILED);
	}
	parse_vec3(tokens[1], (*new_obj)->params);
	parse_vec3(tokens[2], (*new_obj)->params + 3);
	(*new_obj)->params[6] = ft_atod(tokens[3]);
	(*new_obj)->params[7] = ft_atod(tokens[4]);
	parse_color(tokens[5], (*new_obj)->color);
	(*new_obj)->hit = ft_hit_c;
	(*new_obj)->next = NULL;
	return (PARSE_OK);
}

int	parse_cylinder(char **tokens, t_scene *scene)
{
	t_obj	*new_obj;

	if (ft_strncmp(tokens[0], "cy", 3) != 0 || !tokens[1] || !tokens[2]
		|| !tokens[3] || !tokens[4] || !tokens[5])
	{
		print_error("Invalid cylinder format: "
			"cy <pos> <normal> <diameter> <height> <color>");
		return (PARSE_KO);
	}
	if (create_and_fill_cylinder(&new_obj, tokens) != PARSE_OK)
		return (MALLOC_FAILED);
	add_obj_to_scene(&scene->objects, new_obj);
	return (PARSE_OK);
}
