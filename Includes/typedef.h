/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:00:53 by lumugot           #+#    #+#             */
/*   Updated: 2025/07/04 13:22:06 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# include "miniRT.h"

# define L_ERROR "Invalid light format: L <pos x,y,z> <ratio> <color r,g,b>"

typedef struct s_obj	t_obj;
typedef struct s_light	t_light;
typedef unsigned int	t_color[3]; // R, G, B

typedef double			t_vec[3]; // x, y, z
typedef t_vec			t_ray[2]; // pos, dir

/*
Objects can be:
- a sphere 's'
- a plane 'p'
- a cylinder 'c'
*/
typedef	char	(*t_hit_func)(const t_obj *, t_ray);

typedef struct s_obj
{
	char		type; // 's' || 'p' || 'c'
	t_color		color;
	double		*params;
	t_hit_func	hit;
	t_obj		*next;
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
