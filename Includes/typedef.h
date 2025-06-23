/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:00:53 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/23 13:45:05 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# include "miniRT.h"

typedef struct s_obj	t_obj;
typedef unsigned char	t_color[3];

typedef double			t_vec[3]; // x, y, z
typedef t_vec			t_ray[2]; // pos, dir
/*
Objects can be:
- a sphere 's'
- a pyramid 'p'
- a flat 'f'
- a cylinder 'c'
- a light 'l'
*/
typedef struct s_obj
{
	char			type; // 's' || 'p' || 'f' || 'c' || 'l'
	t_color			color;
	const double	*params;
	char			(*hit)(const t_obj obj, t_ray ray);
}	t_obj;

typedef struct s_ambient
{
	double	ratio;
}	t_ambient;

typedef struct s_camera
{
	// t_vec3	position
	// t_vec3	orientation
	int	fov;
}	t_camera;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	int			has_ambient;
	int			his_camera;
}	t_scene;
// 
// typedef struct s_vec3
// {
	// double	x;
    // double	y;
    // double	z;
// }	t_vec3;
// 
// typedef struct s_color
// {
    // double	r;
    // double	g;
    // double	b;
// }	t_color;
// 
// typedef struct s_ambient_light
// {
    // double	ratio;
    // t_color	color;
    // int		is_set;
// }	t_ambient_light;
// 
// typedef struct s_camera
// {
    // t_vec3	origin;
    // t_vec3	orientation;
    // double	fov;
    // int		is_set;
// }	t_camera;
// 
// typedef struct s_light
// {
    // t_vec3	origin;
    // double	brightness;
    // t_color	color;
// }	t_light;
// 
// typedef struct s_sphere
// {
    // t_vec3	center;
    // double	diameter;
    // t_color	color;
// }	t_sphere;
// 
// typedef struct s_plane
// {
    // t_vec3	point;
    // t_vec3	normal;
    // t_color	color;
// }	t_plane;
// 
// typedef struct s_cylinder
// {
    // t_vec3	center;
    // t_vec3	axis;
    // double	diameter;
    // double	height;
    // t_color	color;
// }	t_cylinder;
// 
// typedef enum e_object_type
// {
    // SPHERE,
    // PLANE,
    // CYLINDER
// }	t_object_type;
// 
// typedef struct s_object
// {
    // t_object_type	type;
    // void			*data;
// }	t_object;
// 
// typedef struct s_scene
// {
    // t_ambient_light	ambient_light;
    // t_camera		camera;
    // t_list			*lights;
    // t_list			*objects;
// }	t_scene;
// 
// typedef struct s_data
// {
    // t_scene	scene;
// }	t_data;
// 
#endif
