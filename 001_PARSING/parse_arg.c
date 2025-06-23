/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:41:01 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/23 18:40:03 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/parse.h"

void	print_error(char *message)
{
	ft_putstr_fd("Error: ", 2);
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

void	free_split(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	check_element(char **tokens, t_scene *scene)
{
	(void)scene;
	if (ft_strncmp(tokens[0], "A", 2) == 0)
		// parse_ambient(tokens, scene);
		return (PARSE_OK);
	else if (ft_strncmp(tokens[0], "C", 2) == 0)
		// parse_camera(tokens, scene);
		return (PARSE_OK);
	else if (ft_strncmp(tokens[0], "L", 2) == 0)
		return (PARSE_OK);
	else if (ft_strncmp(tokens[0], "sp", 3) == 0)
		return (PARSE_OK);
	else if (ft_strncmp(tokens[0], "pl", 3) == 0)
		return (PARSE_OK);
	else if (ft_strncmp(tokens[0], "cy", 3) == 0)
		return (PARSE_OK);
	print_error("Unknown identifier");
	return (PARSE_KO);
}

int	dispatch_line(char *line, t_scene *scene)
{
	char	**tokens;
	int		status;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
	{
		free_split(tokens);
		return (PARSE_KO);
	}
	status = check_element(tokens, scene);
	free_split(tokens);
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
		if (line[0] != '\n' && line[0] != '#')
		{
			if (dispatch_line(line, scene) != PARSE_OK)
			{
				status = PARSE_KO;
				break ;
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (status);
}

int	parse_scene(const char *filename, t_scene *scene)
{
	int	fd;
	int	status;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_error("Cannot open scene file !");
		return (PARSE_KO);
	} 
	if (errno == EISDIR)
	{
		print_error(".rt is a folder, not a file !");
		return (PARSE_KO);
	}
	ft_memset(scene, 0, sizeof(t_scene));
	status = read_scene_file(fd, scene);
	close(fd);
	if (status != PARSE_OK)
		return (PARSE_KO);
	if (!scene->ambient_light.is_set || !scene->camera.is_set)
	{
		print_error("Scene must contain one Ambient light and one Camera");
		return (PARSE_KO);
	}
	return (PARSE_OK);
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (check_arg(argc, argv) == PARSE_KO)
		return (1);
	if (parse_scene(argv[1], &scene) == PARSE_KO)
	{
		print_error("Error during parsing !");
		return (1);
	}
	ft_putendl_fd("Parsing successful.", 1);
	return (0);
}
