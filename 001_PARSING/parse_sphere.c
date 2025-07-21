/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:35:20 by lumugot           #+#    #+#             */
/*   Updated: 2025/07/21 14:08:18 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

static int	fill_sphere_data(t_obj *obj, char **tokens)
{
	obj->params = malloc(sizeof(double) * 4);
	if (!obj->params)
		return (MALLOC_FAILED);
	if (parse_vec3(tokens[1], obj->params) == PARSE_KO)
	{
        print_error("Invalid vector for sphere !");
		free(obj->params);
		return (PARSE_KO);
	}
	obj->params[3] = ft_atod(tokens[2]);
	if (parse_color(tokens[3], obj->color) == PARSE_KO)
	{
        print_error("Invalid color for sphere !");
		free(obj->params);
		return (PARSE_KO);
	}
	return (PARSE_OK);
}

int	create_and_fill_sphere(t_obj **new_obj, char **tokens)
{
	int	status;

	*new_obj = malloc(sizeof(t_obj));
	if (!*new_obj)
		return (MALLOC_FAILED);
	ft_memset(*new_obj, 0, sizeof(t_obj));
	status = fill_sphere_data(*new_obj, tokens);
	if (status != PARSE_OK)
	{
		free(*new_obj);
		return (status);
	}
	(*new_obj)->type = 's';
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
		return (PARSE_KO);
	add_obj_to_scene(&scene->objects, new_obj);
	return (PARSE_OK);
}
