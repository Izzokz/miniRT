/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:08:24 by lumugot           #+#    #+#             */
/*   Updated: 2025/07/24 14:45:23 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

static int	validate_cone_vectors(t_obj *obj, char **tokens)
{
	if (parse_vec3(tokens[0], obj->params) == PARSE_KO)
	{
		print_error("Invalid vector for cone !");
		return (PARSE_KO);
	}
	if (parse_vec3(tokens[1], obj->params + 3) == PARSE_KO)
	{
		print_error("Invalid vector for cone !");
		return (PARSE_KO);
	}
	if (obj->params[3] == 0 && obj->params[4] == 0 && obj->params[5] == 0)
	{
		print_error("Cone orientation vector cannot be null");
		return (PARSE_KO);
	}
	return (PARSE_OK);
}

static int	fill_cone_data(t_obj *obj, char **tokens)
{
	obj->params = malloc(sizeof(double) * 8);
	if (!obj->params)
		return (MALLOC_FAILED);
	if (validate_cone_vectors(obj, tokens) == PARSE_KO)
	{
		free(obj->params);
		return (PARSE_KO);
	}
	obj->params[6] = ft_atod(tokens[2]);
	obj->params[7] = ft_atod(tokens[3]);
	if (parse_color(tokens[4], obj->color) == PARSE_KO)
	{
		print_error("Invalid color for cone !");
		free(obj->params);
		return (PARSE_KO);
	}
	return (PARSE_OK);
}

int	create_and_fill_cone(t_obj **new_obj, char **tokens)
{
	int	status;

	*new_obj = malloc(sizeof(t_obj));
	if (!*new_obj)
		return (MALLOC_FAILED);
	ft_memset(*new_obj, 0, sizeof(t_obj));
	status = fill_cone_data(*new_obj, tokens);
	if (status != PARSE_OK)
	{
		free(*new_obj);
		return (status);
	}
	(*new_obj)->hit = ft_hit_cone;
	(*new_obj)->next = NULL;
	return (PARSE_OK);
}

int	parse_cone(char **tokens, t_scene *scene)
{
	t_obj	*new_obj;

	if (!tokens[0] || !tokens[1] || !tokens[2] || !tokens[3] || !tokens[4]
		|| tokens[5])
	{
		print_error("Invalid cone format: "
			"co <pos> <axis> <diameter> <height> <color>");
		return (PARSE_KO);
	}
	if (create_and_fill_cone(&new_obj, tokens) != PARSE_OK)
		return (PARSE_KO);
	add_obj_to_scene(&scene->objects, new_obj);
	return (PARSE_OK);
}
