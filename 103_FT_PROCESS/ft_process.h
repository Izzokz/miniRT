/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:24:51 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/06/05 13:24:52 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PROCESS_H
# define FT_PROCESS_H

# include "../102_FT_OBJ/ft_obj.h"

void	ft_color_scale(t_color edit, const t_color factor);
void	ft_color_add(t_color edit, const t_color sum);
void	ft_color_reflect(t_color edit, const t_color base, float multiplicator);
void	ft_process(t_ray ray, const t_obj *all);

#endif
