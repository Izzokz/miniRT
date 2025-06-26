/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:27:37 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/26 12:56:09 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

static inline int	count_str(char const *str)
{
	int	move;
	int	count;
	int	check_str;

	move = 0;
	count = 0;
	while (str[move])
	{
		check_str = 0;
		while (ft_strchr(" \t\n\v\f\r", str[move]) && str[move])
			move++;
		while (!ft_strchr(" \t\n\v\f\r", str[move]))
		{
			if (check_str == 0)
			{
				count++;
				check_str = 1;
			}
			move++;
		}
	}
	return (count);
}

static inline char	*catch_substring(char const *s, int begin, int ending)
{
	int		p;
	char	*substring;

	substring = malloc(sizeof(char) * (ending - begin + 1));
	if (!substring)
		return (NULL);
	p = -1;
	while (++begin <= ending)
		substring[++p] = s[begin - 1];
	substring[p + 1] = '\0';
	return (substring);
}

static inline char	addition_manager(char **tab, const char *s,
	int *const istart, int j[1])
{
	if (*istart > *(istart + 1))
	{
		*(tab + ++*j) = catch_substring(s, *(istart + 1), *istart);
		if (!*(tab + *j))
		{
			free_tab(tab);
			return (-1);
		}
	}
	return (0);
}

char	**ft_split_space(const char *s)
{
	int		i;
	int		j;
	int		start;
	char	**tab_substrings;

	i = 0;
	j = -1;
	tab_substrings = malloc(sizeof(char *) * (count_str(s) + 1));
	if (!tab_substrings)
		return (NULL);
	while (s[i])
	{
		while (ft_strchr(" \t\n\v\f\r", s[i]) && s[i])
			i++;
		start = i;
		while (!ft_strchr(" \t\n\v\f\r", s[i]))
			i++;
		if (addition_manager(tab_substrings, s, (int [2]){i, start}, &j) < 0)
			return (NULL);
	}
	tab_substrings[j + 1] = NULL;
	return (tab_substrings);
}
