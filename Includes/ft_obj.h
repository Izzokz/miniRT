/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:40:23 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/06/26 19:53:24 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OBJ_H
# define FT_OBJ_H

# include "miniRT.h"

/* OBJ SETTER */
char	ft_init_obj(int i);
char	ft_make_spl(const char type, const t_vec pos,
			const double attr, const t_color color);
char	ft_make_c(const t_vec posnorm[2], const double dia,
			const double height, const t_color color);
char	ft_make_f(const t_vec posnorm[2], const t_color color);

/* OBJ METHODS */
void	ft_reflect(t_ray ray, const t_vec posnorm[2]);
char	ft_hit_s(const t_obj sphere, t_ray ray);
char	ft_hit_p(const t_obj pyramid, t_ray ray);
char	ft_hit_l(const t_obj light, t_ray ray);
char	ft_hit_c(const t_obj cylinder, t_ray ray);
char	ft_hit_f(const t_obj flat, t_ray ray);

/* OBJ FREE FUNCTION */
void	ft_free_obj(void);

/* OBJ GETTER */
t_obj	*ft_get_uninit_obj(void);
t_obj	*ft_get_obj(void);

#endif
