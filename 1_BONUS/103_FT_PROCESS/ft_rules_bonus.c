/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rules_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:42:51 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/11 18:36:45 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

inline void	ft_set_rules_max(t_rules *rules, t_rules *max)
{
	rules->ref = max->ref;
	rules->ref_str = max->ref_str;
	rules->pixel_cross = 1;
	rules->coloration = max->coloration;
}

inline void	ft_init_rules(t_rules *rules)
{
	rules->ref = MRT_MAX_REF;
	rules->ref_str = MRT_MAX_REF_STR;
	rules->pixel_cross = 1;
	rules->coloration = MRT_BEST_COLORATION;
}

inline void	ft_set_rules_min(t_mlx_obj *mobj, t_rules *rules)
{
	if (rules->coloration != ft_color_mini)
	{
		ft_memset(mobj->img_data, 0, mobj->size_line * HEIGHT);
		rules->pixel_cross = MRT_PIXEL_CROSS_PERF;
		rules->coloration = ft_color_mini;
	}
}
