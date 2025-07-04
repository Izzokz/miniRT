/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:29:51 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/06/26 19:42:20 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

inline void	ft_vec_add(t_vec newv, const t_vec v1, const t_vec v2)
{
	ft_new_vec(newv, (*v1 + *v2), *(v1 + 1) + *(v2 + 1),
		*(v1 + 2) + *(v2 + 2));
}

// typedef float	t_vector __attribute__((aligned(16), vector_size(16)));

// [X|Y|Z|W]
// [A|B|C|D]

// [X+A|Y+B|Z+C|W+D]

// typedef union 
// {
// 	t_vector	vec;
// 	struct
// 	{
// 		float x;
// 		float y;
// 		float z;
// 		float w;
// 	};	
// } vec;

// inline vec ft_vec_add(const vec v1, const vec v2)
// {
// 	return (vec)(v1.vec + v2.vec);
// }

inline void	ft_vec_sub(t_vec newv, const t_vec v1, const t_vec v2)
{
	ft_new_vec(newv, (*v1 - *v2), *(v1 + 1) - *(v2 + 1),
		*(v1 + 2) - *(v2 + 2));
}

inline void	ft_vec_scale(t_vec newv, const t_vec v, const double mult)
{
	ft_new_vec(newv, (*v * mult), *(v + 1) * mult,
		*(v + 2) * mult);
}

inline void	ft_vec_div(t_vec newv, const t_vec v, const double div)
{
	ft_new_vec(newv, (*v / div), *(v + 1) / div,
		*(v + 2) / div);
}

inline void	ft_vec_cross(t_vec newv, const t_vec v1, const t_vec v2)
{
	ft_new_vec(newv, *(v1 + 1) * *(v2 + 2) - *(v1 + 2) * *(v2 + 1),
		*(v1 + 2) * *v2 - *v1 * *(v2 + 2), *v1 * *(v2 + 1) - *(v1 + 1) * *v2);
}
