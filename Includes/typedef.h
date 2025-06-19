/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:00:53 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/19 13:15:50 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# include "miniRT.h"

typedef struct s_obj	t_obj;
typedef unsigned char	t_color[3];

typedef double	t_vec[3]; // x, y, z
typedef t_vec	t_ray[2]; // pos, dir
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

#endif