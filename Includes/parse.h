/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:29:33 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/25 10:45:46 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define PARSE_OK 0
# define PARSE_KO 1
# define MALLOC_FAILED -1

# include "miniRT.h"

//parse_arg.c
void	print_error(char *message);
int		check_extension(const char *filename);
int		check_arg(int argc, char **argv);
void	free_split(char **tab);
int		check_element(char **tokens, t_scene *scene);
int		dispatch_line(char *line, t_scene *scene);
int		read_scene_file(int fd, t_scene *scene);
int		parse_scene(const char *filename, t_scene *scene);
int		test(int argc, char **argv);

//parse_elements.c
int		parse_vec3(char *token, t_vec vec);
int		parse_color(char *token, t_color color);
int		parse_ambient(char **tokens, t_scene *scene);
int		parse_camera(char **tokens, t_scene *scene);
int		parse_light(char **tokens, t_scene *scene);
int		parse_sphere(char **tokens, t_scene *scene);
int		parse_plane(char **tokens, t_scene *scene);

#endif