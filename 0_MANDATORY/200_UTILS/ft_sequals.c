/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sequals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:06:10 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/22 13:06:11 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

inline char	ft_sequals(const char *const s1, const char *const s2)
{
	int	i;

	if (!s1 || !s2)
		return (0);
	i = -1;
	while ((*(s1 + ++i) && *(s2 + i)) && *(s1 + i) == *(s2 + i))
		;
	return (*(s1 + i) == *(s2 + i));
}

char	ft_sequals(const char *const s1, const char *const s2);
