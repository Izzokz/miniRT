/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:24:51 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/06/19 13:10:31 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PROCESS_H
# define FT_PROCESS_H

# include "miniRT.h"

void	ft_color_scale(t_color edit, const float factor);
void	ft_color_add(t_color edit, const t_color sum);
void	ft_color_reflect(t_color edit, const t_color base,
			const float multiplicator);
void	ft_process(t_ray ray, const t_obj *all);

#endif
