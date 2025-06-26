/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:11:25 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/26 13:09:12 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

int	parse_light(char **tokens, t_scene *scene)
{
	t_light	*light;
	t_list	*new_node;

	if (ft_strncmp(tokens[0], "L", 2) != 0 || !tokens[1] || !tokens[2] || !tokens[3])
	{
		print_error("Invalid light format: L <pos x,y,z> <ratio> <color r,g,b>");
		return (PARSE_KO);
	}
	light = malloc(sizeof(t_light));
	if (!light)
		return (MALLOC_FAILED);
	if (parse_vec3(tokens[1], light->pos) != PARSE_OK)
	{
		free(light);
		print_error("Invalid light position format");
		return (PARSE_KO);
	}
	light->brightness = ft_atod(tokens[2]);
	if (light->brightness < 0.0 || light->brightness > 1.0)
	{
		free(light);
		print_error("Light brightness ratio must be in range [0.0,1.0]");
		return (PARSE_KO);
	}
	if (parse_color(tokens[3], light->color) != PARSE_OK)
	{
		free(light);
		print_error("Invalid light color");
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

int	parse_sphere(char **tokens, t_scene *scene)
{
	t_obj	*new_obj;
	t_obj	*last;

	if (ft_strncmp(tokens[0], "sp", 3) != 0 || !tokens[1] || !tokens[2] || !tokens[3])
	{
		print_error("Invalid sphere format: sp <pos x,y,z> <diameter> <color r,g,b>");
		return (PARSE_KO);
	}
	new_obj = malloc(sizeof(t_obj));
	if (!new_obj)
		return (MALLOC_FAILED);
	ft_memset(new_obj, 0, sizeof(t_obj));
	new_obj->type = 's';
	new_obj->params = malloc(sizeof(double) * 4);
	if (!new_obj->params)
	{
		free(new_obj);
		return (MALLOC_FAILED);
	}
	parse_vec3(tokens[1], new_obj->params);
	new_obj->params[3] = ft_atod(tokens[2]);
	parse_color(tokens[3], new_obj->color);
	new_obj->next = NULL;
	if (!scene->objects)
		scene->objects = new_obj;
	else
	{
		last = scene->objects;
		while (last->next)
			last = last->next;
		last->next = new_obj;
	}
	return (PARSE_OK);
}

int	parse_plane(char **tokens, t_scene *scene)
{
	t_obj	*new_obj;
	t_obj	*last;

	if (ft_strncmp(tokens[0], "pl", 3) != 0 || !tokens[1] || !tokens[2] || !tokens[3])
	{
		print_error("Invalid plane format: sp <pos x,y,z> <normal a,b,c> <color r,g,b>");
		return (PARSE_KO);
	}
	new_obj = malloc(sizeof(t_obj));
	if (!new_obj)
		return (MALLOC_FAILED);
	ft_memset(new_obj, 0, sizeof(t_obj));
	new_obj->type = 'p';
	new_obj->params = malloc(sizeof(double) * 6);
	if (!new_obj->params)
	{
		free(new_obj);
		return (MALLOC_FAILED);
	}
	parse_vec3(tokens[1], new_obj->params);
	parse_vec3(tokens[2], new_obj->params + 3);
	parse_color(tokens[3], new_obj->color);
	new_obj->next = NULL;
	if (!scene->objects)
		scene->objects = new_obj;
	else
	{
		last = scene->objects;
		while (last->next)
			last = last->next;
		last->next = new_obj;
	}
	return (PARSE_OK);
}

int	parse_cylinder(char **tokens, t_scene *scene)
{
	t_obj	*new_obj;
	t_obj	*last;

	if (ft_strncmp(tokens[0], "cy", 3) != 0 || !tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5])
	{
		print_error("Invalid cylinder format: cy <pos x,y,y> <normal a,b,c> <diameter> <height> <color r,g,b>");
		return(PARSE_KO);
	}
	new_obj = malloc(sizeof(t_obj));
	if (!new_obj)
		return (MALLOC_FAILED);
	ft_memset(new_obj, 0, sizeof(t_obj));
	new_obj->type = 'c';
	new_obj->params = malloc(sizeof(double) * 8);
	if (!new_obj->params)
	{
		free(new_obj);
		return (MALLOC_FAILED);
	}
	parse_vec3(tokens[1], new_obj->params);
	parse_vec3(tokens[2], new_obj->params + 3);
	new_obj->params[6] = ft_atod(tokens[3]);
	new_obj->params[7] = ft_atod(tokens[4]);
	parse_color(tokens[5], new_obj->color);
	new_obj->next = NULL;
	if (!scene->objects)
		scene->objects = new_obj;
	else
	{
		last = scene->objects;
		while (last->next)
			last = last->next;
		last->next = new_obj;
	}
	return (PARSE_OK);
}
