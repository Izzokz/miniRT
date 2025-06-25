/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:00:53 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/25 20:35:12 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# include "miniRT.h"

typedef struct s_obj	t_obj;
typedef struct s_light	t_light;
typedef unsigned char	t_color[3]; // R, G, B

typedef double			t_vec[3]; // x, y, z
typedef t_vec			t_ray[2]; // pos, dir

/*
Objects can be:
- a sphere 's'
- a plane 'p'
- a cylinder 'c'
*/

typedef struct s_obj
{
	char	type; // 's' || 'p' || 'c'
	t_color	color;
	double	*params;
	char	(*hit)(const t_obj *obj, t_ray ray);
	t_obj	*next;
}	t_obj;

typedef struct s_light
{
	t_color	color;
	t_vec	pos;
	double	brightness;
	t_light	*next;
}	t_light;

typedef struct s_keys
{
	unsigned char	w : 1;
	unsigned char	a : 1;
	unsigned char	s : 1;
	unsigned char	d : 1;
	unsigned char	ctrl : 1;
	unsigned char	esc : 1;
}	t_keys;

typedef struct s_mlx_obj
{
	void	*mlx;
	int		win_i;
	int		win_j;
	void	*win;
	void	*img;
}	t_mlx_obj;

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
	int		is_set;
}	t_ambient;

typedef struct s_camera
{
	t_vec	pos;
	t_vec	orientation;
	double	fov;
	int		is_set;
}	t_camera;

typedef struct s_scene
{
	t_ambient	ambient_light;
	t_camera	camera;
	t_list		*lights;
	t_obj		*objects;
}	t_scene;

#endif
