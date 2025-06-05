/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:40:23 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/05/29 14:40:24 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OBJ_H
# define FT_OBJ_H

# include "../101_FT_VEC/ft_vec.h"

typedef struct s_obj	t_obj;
typedef unsigned char	t_color[3];

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

/* OBJ SETTER */
char	ft_init_obj(int i);
char	ft_make_spl(char type, t_vec pos, double attr, t_color color);
char	ft_make_c(t_vec posnorm[2], double dia_hei[2], t_color color);
char	ft_make_f(t_vec posnorm[2], t_color color);

/* OBJ METHODS */
void	ft_reflect(t_ray ray, const t_vec posnorm[2]);
char	ft_hit_s(const t_obj sphere, t_ray ray);
char	ft_hit_p(const t_obj pyramid, t_ray ray);
char	ft_hit_l(const t_obj light, t_ray ray);
char	ft_hit_c(const t_obj cylinder, t_ray ray);
char	ft_hit_f(const t_obj flat, t_ray ray);

/* OBJ FREE FUNCTION */
void	ft_free_obj(t_obj *all);

/* OBJ GETTER */
t_obj	*ft_get_uninit_obj(void);
t_obj	*ft_get_obj(void);

#endif
