/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:24:23 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/19 13:25:20 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	if (!str)
		return (0);
	while (str[count])
		count++;
	return (count);
}

size_t	ft_line_len(const char *str)
{
	size_t	count;

	count = 0;
	while (str[count] && str[count] != '\n')
		count++;
	if (str[count] == '\n')
		count++;
	return (count);
}

int	ft_strchr_endl(const char *str, char c)
{
	int	index;

	index = 0;
	if (!str)
		return (0);
	while (str[index])
	{
		if (str[index] == c)
			return (1);
		index++;
	}
	return (0);
}

char	*ft_strjoin_buf(char *s1, char *s2)
{
	size_t		i;
	size_t		j;
	size_t		full_size;
	char		*tab;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	full_size = ft_strlen(s1) + ft_strlen(s2);
	tab = malloc(sizeof(char) * full_size + 1);
	if (!tab)
		return (NULL);
	while (s1[i] && s1)
	{
		tab[i] = s1[i];
		i++;
	}
	while (s2[j])
		tab[i++] = s2[j++];
	tab[i] = '\0';
	free(s1);
	return (tab);
}
