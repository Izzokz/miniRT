/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:00:53 by lumugot           #+#    #+#             */
/*   Updated: 2025/08/09 18:16:59 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# define WIDTH 1000 // INIT : 1069
# define HEIGHT 800  // INIT : 690
# define MOVE_SPEED .050 // INIT : .069
# define ROT_SPEED .0060 // INIT : .069
# define PHONG_SHININESS 6.9 // INIT : 6.9
# define MRT_MAX_REF 100 // INIT : 4
# define MRT_MAX_REF_STR 1.0 // INIT : .30035

# ifdef MRT_BEST_COLORATION
#  undef MRT_BEST_COLORATION
# endif

/* *** CRITICAL MACRO *** */
// ==============================================================
// Change with an existing function taking the right parameters
// 	|unsigned int	f(t_ray, t_obj *, t_scene *, const t_rules *)
// - the ray comes from a hit object
// - the object is the one hit
// - the scene is the scene like the rules are unique
// Please do not use ft_color_mini ;_;
// ==============================================================
/* *** CRITICAL MACRO *** */
# define MRT_BEST_COLORATION ft_blend_color // INIT : ft_blend_color

# ifdef PI
#  undef PI
# endif

/* *** CRITICAL MACRO *** */
// =======================
// Why wanting to edit PI?
// =======================
/* *** CRITICAL MACRO *** */
# define PI 3.141592653589793

# ifdef MRT_PIXEL_CROSS_PERF
#  undef MRT_PIXEL_CROSS_PERF
# endif

/* *** CRITICAL MACRO *** */
// =======================================
// This macro is not protected.
// If you really need to edit it, ensure :
// !(MRT_PIXEL_CROSS_PERF <= 0)
// == SPEED FACTOR (on displacement).
// =======================================
/* *** CRITICAL MACRO *** */
# define MRT_PIXEL_CROSS_PERF 8 // INIT : 8

# ifdef MRT_MAX_REF
#  undef MRT_MAX_REF
# endif

/* *** CRITICAL MACRO *** */
// =========================================
// This macro is not protected.
// If you want to edit it, ensure :
// !(MRT_MAX_REF <= 0 || MRT_MAX_REF >= 255)
// Note that it involves MRT_SHADOW_SAMPLES.
// For example : MRT_SHADOW_SAMPLES is set
// to 100 and this macro to 100, it will be
// equivalent to this macro set to 10000.
// == SPEED FACTOR.
// =========================================
# define MRT_MAX_REF 10 // INIT : 4 | BEST : 100

# ifdef MRT_SHADOW_SAMPLES
#  undef MRT_SHADOW_SAMPLES
# endif

/* *** CRITICAL MACRO *** */
// ======================================================
// This macro is not protected.
// If you want to edit it, ensure :
// !(MRT_SHADOW_SAMPLES <= 0 || MRT_SHADOW_SAMPLES >= 255)
// Note that it depends on MRT_MAX_REF meaning it is
// MRT_MAX_REF times slower. For example : MRT_MAX_REF
// is set to 100 and this macro to 100, it will be
// equivalent to this macro set to 10000.
// == SPEED FACTOR.
// ======================================================
/* *** CRITICAL MACRO *** */
# define MRT_SHADOW_SAMPLES 1 // INIT : 1 | BEST : 100

# ifdef MRT_LIGHT_RADIUS
#  undef MRT_LIGHT_RADIUS
# endif

/* *** CRITICAL MACRO *** */
// ================================
// This macro is not protected.
// If you want to edit it, ensure :
// MRT_LIGHT_RADIUS != 0
// ================================
/* *** CRITICAL MACRO *** */
# define MRT_LIGHT_RADIUS 0.0 // INIT : .69

typedef struct s_obj	t_obj;
typedef struct s_light	t_light;
typedef struct s_rules	t_rules;
typedef unsigned char	t_color[3]; // R, G, B

typedef double			t_vec[3]; // x, y, z
typedef t_vec			t_ray[2]; // pos, dir

/*
Objects can be:\
- a sphere 's'
- a plane 'p'
- a cylinder 'c'
*/
typedef struct s_obj
{
	t_color	color;
	double	*params;
	char	type;
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

/* *** CRITICAL STRUCT *** */
// ==============================================
// DO NOT CHANGE THE ORDER OF COMMENTED VARIABLES
// ==============================================
/* *** CRITICAL STRUCT *** */
typedef struct __attribute__((__packed__)) s_keys
{
	unsigned char	a : 1; //
	unsigned char	d : 1; //
	unsigned char	shift : 1; //
	unsigned char	space : 1; //
	unsigned char	s : 1; //
	unsigned char	w : 1; //
	unsigned char	left : 1;
	unsigned char	right : 1;
	unsigned char	down : 1;
	unsigned char	up : 1;
	unsigned char	q : 1;
	unsigned char	e : 1;
	unsigned char	ctrl : 1;
	unsigned char	esc : 1;
	unsigned char	r : 1;
	unsigned char	c : 1;
	unsigned char	reset : 1;
	unsigned char	tab : 1;
	unsigned char	tab_triggd : 1;
	unsigned char	t : 1;
    unsigned char	key_1 : 1;
    unsigned char	key_1_triggd : 1;
    unsigned char	key_2 : 1;
    unsigned char	key_2_triggd : 1;
    unsigned char	key_3 : 1;
    unsigned char	key_3_triggd : 1;
	unsigned char	p_up : 1;
	unsigned char	p_down : 1;
	unsigned char	r_speed_up : 1;
	unsigned char	r_speed_down : 1;
}	t_keys;

/* *** CRITICAL STRUCT *** */
// ==============================================
// DO NOT CHANGE THE ORDER OF COMMENTED VARIABLES
// ==============================================
/* *** CRITICAL STRUCT *** */
typedef struct s_mlx_obj
{
	int		win_i;
	int		win_j;
	void	*mlx;
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

/* *** CRITICAL STRUCT *** */
// ========================================
// DO NOT CHANGE THE ORDER OF THE VARIABLES
// ========================================
/* *** CRITICAL STRUCT *** */
typedef struct s_camera
{
	t_vec			pos;
	t_vec			orientation;
	double			fov;
	int				is_set;
}	t_camera;

typedef struct s_scene
{
	t_ambient		ambient_light;
	t_camera		camera;
	t_light			*lights;
	t_obj			*objects;
	t_ray			ray;
	int				coords[2];
	t_vec			_right;
	t_vec			_up;
	t_vec			_forward;
	double			_pitch;
	double			_yaw;
	double			_roll;
	double			m_speed;
	double			r_speed;
	double			mult;
}	t_scene;

typedef struct s_rules
{
	unsigned char	ref;
	char			pixel_cross;
	double			ref_str;
	unsigned int	(*coloration)(t_ray, t_obj *hit,
			t_scene *, const t_rules *);
	unsigned char	menu_state : 3;
}	t_rules;

typedef struct s_color_ads
{
	t_color	ambient;
	t_color	diffuse[2];
	t_color	specular[2];
}	t_color_ads;

#endif
