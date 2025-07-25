/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:59:42 by lumugot           #+#    #+#             */
/*   Updated: 2025/07/21 14:20:43 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

void	print_error(char *message)
{
	ft_putendl_fd("\033[0;31mError\033[0m", 2);
	ft_putendl_fd(message, 2);
}

int	check_extension(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + (len - 3), ".rt", 4) != 0)
	{
		print_error("Scene file must have a .rt extension.");
		return (PARSE_KO);
	}
	return (PARSE_OK);
}

int	check_arg(int argc, char **argv)
{
	if (argc != 2)
	{
		print_error("Invalid number of arguments");
		ft_putendl_fd("Usage: ./miniRT <scene.rt>", 2);
		return (PARSE_KO);
	}
	if (check_extension(argv[1]) != PARSE_OK)
		return (PARSE_KO);
	return (PARSE_OK);
}

int	check_element(char **tokens, t_scene *scene)
{
	int	status;

	status = PARSE_KO;
	(void)scene;
	if (ft_strncmp(tokens[0], "A", 2) == 0)
		status = parse_ambient(++tokens, scene);
	else if (ft_strncmp(tokens[0], "C", 2) == 0)
		status = parse_camera(++tokens, scene);
	else if (ft_strncmp(tokens[0], "L", 2) == 0)
		status = parse_light(++tokens, scene);
	else if (ft_strncmp(tokens[0], "sp", 3) == 0)
		status = parse_sphere(++tokens, scene);
	else if (ft_strncmp(tokens[0], "pl", 3) == 0)
		status = parse_plane(++tokens, scene);
	else if (ft_strncmp(tokens[0], "cy", 3) == 0)
		status = parse_cylinder(++tokens, scene);
	else if (!ft_strncmp(*tokens, "c3", 3))
		status = parse_cube(++tokens, scene);
	else if (!ft_strncmp(*tokens, "co", 3))
		status = parse_cone(++tokens, scene);
	else
		print_error("Unknown identifier");
	return (status);
}
