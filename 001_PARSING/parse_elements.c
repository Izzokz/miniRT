/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:11:25 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/24 15:25:25 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

static int	parse_vec3(char *token, t_vec vec)
{
    char	**components;

    components = ft_split(token, ',');
    if (!components || !components[0] || !components[1] || !components[2]
        || components[3])
    {
        free_split(components);
        return (PARSE_KO);
    }
    vec[0] = ft_atod(components[0]);
    vec[1] = ft_atod(components[1]);
    vec[2] = ft_atod(components[2]);
    free_split(components);
    return (PARSE_OK);
}

static int	parse_color(char *token, t_color color)
{
	char	**components;
	int		i;

	i = 0;
	components = ft_split(token, ',');
	if (!components || !components[0] || !components[1] || !components[2])
	{
		free_split(components);
		return (PARSE_KO);
	}
	while (i < 3)
	{
		color[0] = ft_atod(components[i]);
		if (color[0] < 0 || color[0] > 255)
		{
			free_split(components);
			return (PARSE_KO);
		}
		i++;
	}
	free_split(components);
	return (PARSE_OK);
}

int	parse_ambient(char **tokens, t_scene *scene)
{
	if (scene->ambient_light.is_set)
	{
		print_error("Ambient light already set");
		return (PARSE_KO);
	}
	if (ft_strncmp(tokens[0], "A", 2) != 0 || !tokens[1] || !tokens[2])
	{
		print_error("Invalid ambient light format");
		return (PARSE_KO);
	}
	scene->ambient_light.ratio = ft_atod(tokens[1]);
	if (scene->ambient_light.ratio < 0 || scene->ambient_light.ratio > 1)
	{
		print_error("Ambient light ratio must be between 0 and 1");
		return (PARSE_KO);
	}
	if (parse_color(tokens[2], &scene->ambient_light.color) != PARSE_OK)
	{
		print_error("Invalid ambient light color");
		return (PARSE_KO);
	}
	scene->ambient_light.is_set = 1;
	return (PARSE_OK);
}

int	parse_camera(char **tokens, t_scene *scene)
{
	if (scene->camera.is_set)
	{
		print_error("Camera already set");
		return (PARSE_KO);
	}
	if (ft_strncmp(tokens[0], "C", 2) != 0 || !tokens[1] || !tokens[2] || !tokens[3])
	{
		print_error("Invalid camera format");
		return (PARSE_KO);
	}
	scene->camera.fov = ft_atoi(tokens[1]);
	if (scene->camera.fov <= 0 || scene->camera.fov >= 180)
	{
		print_error("Camera FOV must be between 0 and 180 degrees");
		return (PARSE_KO);
	}
	scene->camera.is_set = 1;
	return (PARSE_OK);
}

int	parse_light(char **tokens, t_scene *scene)
{
    t_light	*light;
    t_list	*new_node;

    if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
    {
        print_error("Invalid light format: L <pos x,y,z> <ratio> <color r,g,b>");
        return (PARSE_KO);
    }
    light = malloc(sizeof(t_light));
    if (!light)
		return (MALLOC_FAILED);
    if (parse_vec3(tokens[1], &light->pos) != PARSE_OK)
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
    if (parse_color(tokens[3], &light->color) != PARSE_OK)
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

int	parse_plane(char **token, t_scene scene)
{
	
}