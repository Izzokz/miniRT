/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 21:41:01 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/11 18:31:40 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	ft_free_lights(t_light *head)
{
	t_light	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}
