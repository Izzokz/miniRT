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

# include "typedef.h"

/* OBJ METHODS */
void	ft_reflect(t_ray, t_vec posnorm[2]);
char	ft_c3_reflect(t_ray ray, t_ray local,
			t_vec axes_c3pos[4], double minhalf[2]);
char	ft_hit_s(const t_obj *sphere, t_ray ray);
char	ft_hit_c(const t_obj *cylinder, t_ray ray);
char	ft_hit_p(const t_obj *plane, t_ray ray);
char	ft_hit_c3(const t_obj *cube, t_ray ray);

/* OBJ FREE FUNCTION */
void	ft_free_obj(t_obj *head);
void	ft_free_light(t_light *head);

#endif
