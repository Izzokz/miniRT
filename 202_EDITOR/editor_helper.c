/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:28:50 by lumugot           #+#    #+#             */
/*   Updated: 2025/08/10 20:26:59 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Includes/miniRT.h"

void	ft_putstr_color(const char *str, int color)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	if (!str)
		return ;
	printf("\033[38;2;%d;%d;%dm%s\033[0m", r, g, b, str);
}

void	explain_editor(void)
{
	ft_putstr_color(NB_OBJECT, COL_PEACH);
	ft_putstr_color(EX_CHANGE, COL_PEACH);
	ft_putstr_color(EX_1, COL_PEACH);
	ft_putstr_color(KEEP_PARAMS, COL_PEACH);
	ft_putstr_color(EX_2, COL_PEACH);
	ft_putstr_color(SET_PARAMS, COL_MINT);
}
