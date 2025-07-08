/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:00:53 by lumugot           #+#    #+#             */
/*   Updated: 2025/07/06 23:27:04 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# define L_ERROR "Invalid light format: L <pos x,y,z> <ratio> <color r,g,b>"
# define WIDTH 900
# define HEIGHT 800
# define MOVE_SPEED 0.18
# define ROT_SPEED 0.05

# ifdef PI
#  undef PI
# endif

# define PI 3.141592653589793

typedef struct s_obj	t_obj;
typedef struct s_light	t_light;
typedef struct s_rules	t_rules;
typedef unsigned char	t_color[3]; // R, G, B

typedef double			t_vec[3]; // x, y, z
typedef t_vec			t_ray[2]; // pos, dir

/* Gimbal Lock Information (Unlock) */
typedef struct __attribute__((__packed__)) s_gl_info
{
	char	occured;
	char	axis;
	void	(*unlock)(t_vec dir, char gli[2]);
	void	(*realign)(t_vec dir, char gli[2]);
}	t_gl_info;

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
	char	(*hit)(const t_obj *self, t_ray);
	t_obj	*next;
}	t_obj;

typedef struct s_light
{
	t_color	color;
	t_vec	pos;
	double	brightness;
	t_light	*next;
}	t_light;

typedef struct __attribute__((__packed__)) s_keys
{
	unsigned char	a : 1;
	unsigned char	d : 1;
	unsigned char	shift : 1;
	unsigned char	space : 1;
	unsigned char	s : 1;
	unsigned char	w : 1;
	unsigned char	left : 1;
	unsigned char	right : 1;
	unsigned char	down : 1;
	unsigned char	up : 1;
	unsigned char	alt_r : 1;
	unsigned char	ctrl_r : 1;
	unsigned char	esc : 1;
	unsigned char	r : 1;
}	t_keys;

typedef struct s_mlx_obj
{
	void	*mlx;
	int		win_i;
	int		win_j;
	void	*win;
	void	*img;
	char	*img_data;
	int		bpp;
	int		size_line;
}	t_mlx_obj;

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
	int		is_set;
}	t_ambient;

typedef struct s_camera
{
	t_vec		pos;
	t_vec		orientation;
	double		fov;
	int			is_set;
	t_gl_info	gli;
}	t_camera;

typedef struct s_scene
{
	t_ambient	ambient_light;
	t_camera	camera;
	t_light		*lights;
	t_obj		*objects;
	t_ray		ray;
}	t_scene;

typedef struct __attribute__((__packed__)) s_viewport
{
	t_vec	hor;
	t_vec	ver;
	t_vec	pos;
}	t_viewport;

typedef struct s_rules
{
	char			ref;
	char			pixel_cross;
	double			ref_str;
	unsigned int	(*coloration)(t_ray, t_obj *hit,
			const t_scene *, const t_rules *);
}	t_rules;

typedef struct s_color_ads
{
	t_color	ambient;
	t_color	diffuse[2];
	t_color	specular[2];
}	t_color_ads;

#endif
