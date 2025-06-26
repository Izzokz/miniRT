/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:29:33 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/26 18:38:03 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define PARSE_OK 0
# define PARSE_KO 1
# define MALLOC_FAILED -1

# include "miniRT.h"

//check_scene.c
void	print_error(char *message);
int		check_extension(const char *filename);
int		check_arg(int argc, char **argv);
int		check_element(char **tokens, t_scene *scene);

//parse_arg.c
int		dispatch_line(char *line, t_scene *scene);
int		read_scene_file(int fd, t_scene *scene);
int		parse_scene(const char *filename, t_scene *scene);

//parse_params.c
int		parse_vec3(char *token, t_vec vec);
int		parse_color(char *token, t_color color);
int		parse_ambient(char **tokens, t_scene *scene);
int		parse_camera(char **tokens, t_scene *scene);
int		parse_light(char **tokens, t_scene *scene);

//parse_light.c
int		fill_light_data(t_light *light, char **tokens);
int		parse_light(char **tokens, t_scene *scene);

//parse_plane.c
int		create_and_fill_plane(t_obj **new_obj, char **tokens);
int		parse_plane(char **tokens, t_scene *scene);

//parse_sphere.c
int		create_and_fill_sphere(t_obj **new_obj, char **tokens);
int		parse_sphere(char **tokens, t_scene *scene);

//parse_cylinder.c
void	add_obj_to_scene(t_obj **objects, t_obj *new_obj);
int		create_and_fill_cylinder(t_obj **new_obj, char **tokens);
int		parse_cylinder(char **tokens, t_scene *scene);

//free_utils.c
void	free_tab(char **tab);
void	free_objects(t_obj *obj);
void	free_lights(t_list *lights);
void	free_scene(t_scene *scene);

#endif