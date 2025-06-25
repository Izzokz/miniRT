/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:41:01 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/25 20:35:46 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/parse.h"

void	print_error(char *message)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(message, 2);
}

static void	free_tab(char **tab)
{
	int	iter;

	iter = 0;
	while (tab[iter])
	{
		free(tab[iter]);
		iter++;
	}
	free(tab);
}

static inline int	count_str(char const *str)
{
	int	move;
	int	count;
	int	check_str;

	move = 0;
	count = 0;
	while (str[move])
	{
		check_str = 0;
		while (ft_strchr(" \t\n\v\f\r", str[move]) && str[move])
			move++;
		while (!ft_strchr(" \t\n\v\f\r", str[move]))
		{
			if (check_str == 0)
			{
				count++;
				check_str = 1;
			}
			move++;
		}
	}
	return (count);
}

static inline char	*catch_substring(char const *s, int begin, int ending)
{
	int		p;
	char	*substring;

	substring = malloc(sizeof(char) * (ending - begin + 1));
	if (!substring)
		return (NULL);
	p = -1;
	while (++begin <= ending)
		substring[++p] = s[begin - 1];
	substring[p + 1] = '\0';
	return (substring);
}

static inline char	addition_manager(char **tab, const char *s,
	int *const istart, int j[1])
{
	if (*istart > *(istart + 1))
	{
		*(tab + ++*j) = catch_substring(s, *(istart + 1), *istart);
		if (!*(tab + *j))
		{
			free_tab(tab);
			return (-1);
		}
	}
	return (0);
}

char	**ft_split_space(const char *s)
{
	int		i;
	int		j;
	int		start;
	char	**tab_substrings;

	i = 0;
	j = -1;
	tab_substrings = malloc(sizeof(char *) * (count_str(s) + 1));
	if (!tab_substrings)
		return (NULL);
	while (s[i])
	{
		while (ft_strchr(" \t\n\v\f\r", s[i]) && s[i])
			i++;
		start = i;
		while (!ft_strchr(" \t\n\v\f\r", s[i]))
			i++;
		if (addition_manager(tab_substrings, s, (int [2]){i, start}, &j) < 0)
			return (NULL);
	}
	tab_substrings[j + 1] = NULL;
	return (tab_substrings);
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
		parse_ambient(tokens, scene);
	else if (ft_strncmp(tokens[0], "C", 2) == 0)
		parse_camera(tokens, scene);
	else if (ft_strncmp(tokens[0], "L", 2) == 0)
		parse_light(tokens, scene);
	else if (ft_strncmp(tokens[0], "sp", 3) == 0)
		parse_sphere(tokens, scene);
	else if (ft_strncmp(tokens[0], "pl", 3) == 0)
		parse_plane(tokens, scene);
	else if (ft_strncmp(tokens[0], "cy", 3) == 0)
		return (PARSE_OK);
	else
	{
		print_error("Unknown identifier");
		return (PARSE_KO);
	}
	return (PARSE_OK);
}

int	dispatch_line(char *line, t_scene *scene)
{
	char	**tokens;
	int		status;

	tokens = ft_split_space(line);
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
	int		fd;
	int		status;
	char	buffer;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_error("Cannot open scene file !");
		return (PARSE_KO);
	}
	if (read(fd, &buffer, 0) == -1)
	{
		print_error(".rt is not file, it's a folder !");
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

int	test(int argc, char **argv)
{
	t_scene	scene;

	if (check_arg(argc, argv) == PARSE_KO)
		return (PARSE_KO);
	if (parse_scene(argv[1], &scene) == PARSE_KO)
		return (PARSE_KO);
	return (PARSE_OK);
}
