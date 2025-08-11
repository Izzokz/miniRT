/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:41:01 by lumugot           #+#    #+#             */
/*   Updated: 2025/07/21 14:15:03 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/parse.h"

int	dispatch_line(char *line, t_scene *scene)
{
	char	**tokens;
	int		status;

	tokens = ft_split_space(line);
	if (!tokens || !tokens[0])
	{
		free_tab(tokens);
		return (PARSE_KO);
	}
	status = check_element(tokens, scene);
	free_tab(tokens);
	return (status);
}

int	read_scene_file(int fd, t_scene *scene)
{
	char	*line;
	int		status;

	status = PARSE_OK;
	line = get_next_line(fd);
	while (line)
	{
		if (status == PARSE_OK && line[0] != '\n' && line[0] != '#')
		{
			if (dispatch_line(line, scene) != PARSE_OK)
				status = PARSE_KO;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (status);
}

int	parse_scene(const char *filename, t_scene *scene)
{
	int		fd;
	int		status;
	char	buffer;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_error("Cannot open scene file !");
		exit(PARSE_KO);
	}
	if (read(fd, &buffer, 0) == -1)
	{
		print_error(".rt is not file !");
		close(fd);
		exit(PARSE_KO);
	}
	ft_memset(scene, 0, sizeof(t_scene));
	status = read_scene_file(fd, scene);
	close(fd);
	if (!scene->ambient_light.is_set || !scene->camera.is_set)
	{
		print_error("Scene must contain one Ambient light and one Camera");
		return (PARSE_KO);
	}
	return (status);
}
