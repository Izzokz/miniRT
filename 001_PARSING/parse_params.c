/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:39:47 by lumugot           #+#    #+#             */
/*   Updated: 2025/07/21 14:11:48 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

int	parse_vec3(char *token, t_vec vec)
{
	char	**components;
	int		index;

	components = ft_split(token, ',');
	if (!components || !components[0] || !components[1] || !components[2])
	{
		free_tab(components);
		return (PARSE_KO);
	}
	index = 0;
	while (index < 3)
	{
		if (is_valid_params(components[index]) == PARSE_KO)
		{
			free_tab(components);
			return (PARSE_KO);
		}
		index++;
	}
	vec[0] = ft_atod(components[0]);
	vec[1] = ft_atod(components[1]);
	vec[2] = ft_atod(components[2]);
	free_tab(components);
	return (PARSE_OK);
}

int	parse_color(char *token, t_color color)
{
	char	**components;
	double	tmp;
	int		i;

	i = 0;
	components = ft_split(token, ',');
	if (!components || !components[0] || !components[1] || !components[2])
	{
		free_tab(components);
		return (PARSE_KO);
	}
	while (i < 3)
	{
		if (is_valid_params(components[i]) == PARSE_KO)
		{
			free_tab(components);
			return (PARSE_KO);
		}
		tmp = ft_atod(components[i]);
		if (tmp < 0 || tmp > 255)
		{
			free_tab(components);
			return (PARSE_KO);
		}
		*(color + i) = tmp;
		i++;
	}
	free_tab(components);
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
	scene->ambient_light.is_set = 1;
	if (scene->ambient_light.ratio < 0 || scene->ambient_light.ratio > 1)
	{
		print_error("Ambient light ratio must be between 0 and 1");
		return (PARSE_KO);
	}
	if (parse_color(tokens[2], scene->ambient_light.color) != PARSE_OK)
	{
		print_error("Invalid ambient light color");
		return (PARSE_KO);
	}
	return (PARSE_OK);
}

int	parse_camera(char **tokens, t_scene *scene)
{
	if (scene->camera.is_set)
	{
		print_error("Camera already set");
		return (PARSE_KO);
	}
	if (ft_strncmp(tokens[0], "C", 2) != 0 || !tokens[1] || !tokens[2]
		|| !tokens[3])
	{
		print_error("Invalid camera format");
		return (PARSE_KO);
	}
	scene->camera.fov = ft_atod(tokens[3]);
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
	{
		print_error("Camera FOV must be between 0 and 180 degrees");
		return (PARSE_KO);
	}
	scene->camera.is_set = 1;
	if (parse_vec3(tokens[1], scene->camera.pos) == PARSE_KO)
	{
		print_error("Invalid camera position vector");
		return (PARSE_KO);
	}
	if (parse_vec3(tokens[2], scene->camera.orientation) == PARSE_KO)
	{
		print_error("Invalid camera orientation vector");
		return (PARSE_KO);
	}
	if (scene->camera.fov >= 0 && scene->camera.fov <= 180)
		return (PARSE_OK);
	print_error("Camera FOV must be between 0 and 180 degrees");
	return (PARSE_KO);
}
