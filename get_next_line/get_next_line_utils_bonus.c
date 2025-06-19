/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:28:18 by lumugot           #+#    #+#             */
/*   Updated: 2024/11/06 15:18:48 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

int	ft_strchr(const char *str, char c)
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

char	*ft_strjoin(char *s1, char *s2)
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
	while (s1 && s1[i])
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
