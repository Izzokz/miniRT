/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:25:56 by lumugot           #+#    #+#             */
/*   Updated: 2025/08/09 16:17:44 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

int	validate_camera(char **tokens, t_scene *scene)
{
	scene->camera.fov = ft_atod(tokens[2]);
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
	{
		print_error("Camera FOV must be in range [0,180]");
		return (PARSE_KO);
	}
	if (parse_vec3(tokens[0], scene->camera.pos) == PARSE_KO)
	{
		print_error("Invalid camera position vector");
		return (PARSE_KO);
	}
	if (parse_vec3(tokens[1], scene->camera.orientation) == PARSE_KO)
	{
		print_error("Invalid camera orientation vector");
		return (PARSE_KO);
	}
	if (scene->camera.orientation[0] == 0 && scene->camera.orientation[1] == 0
		&& scene->camera.orientation[2] == 0)
	{
		print_error("Camera orientation vector cannot be null");
		return (PARSE_KO);
	}
	scene->camera.is_set = 1;
	ft_vec_norm(scene->camera.orientation, scene->camera.orientation);
	return (PARSE_OK);
}

int	parse_camera(char **tokens, t_scene *scene)
{
	if (scene->camera.is_set)
	{
		print_error("Camera already set");
		return (PARSE_KO);
	}
	if (!tokens[0] || !tokens[1] || !tokens[2] || tokens[3])
	{
		print_error("Invalid camera format");
		return (PARSE_KO);
	}
	return (validate_camera(tokens, scene));
}
