/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:05:26 by kzhen-cl          #+#    #+#             */
/*   Updated: 2024/11/01 14:28:34 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	free_all(char **buffer, char **temp_str)
{
	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	if (*temp_str)
	{
		free(*temp_str);
		*temp_str = NULL;
	}
}

static int	endl_in(char *buffer)
{
	int	i;

	i = -1;
	while (buffer[++i])
		if (buffer[i] == '\n')
			return (1);
	return (0);
}

static int	process_return(char **buffer, char **temp_str)
{
	size_t	i;
	size_t	j;

	i = -1;
	if (!ft_strlen(*buffer))
		return (-1);
	while ((*buffer)[++i] && (*buffer)[i] != '\n')
		;
	if (!(*buffer)[i])
		return (0);
	*temp_str = ft_calloc(ft_strlen(*buffer) - i, 1);
	if (!(*temp_str))
		return (-1);
	j = -1;
	while ((*buffer)[++i])
	{
		(*temp_str)[++j] = (*buffer)[i];
		(*buffer)[i] = '\0';
	}
	return (0);
}

static int	search_next_line(char **buffer, char **temp_str, int fd)
{
	int	term;

	while (!endl_in(*buffer))
	{
		if (*temp_str)
			free_all(temp_str, temp_str);
		*temp_str = ft_calloc(BUFFER_SIZE + 1, 1);
		if (!(*temp_str))
			return (-1);
		term = read(fd, *temp_str, BUFFER_SIZE);
		if (term == -1)
			return (-1);
		*buffer = ft_strjoinfree(buffer, temp_str);
		if (!(*buffer))
			return (-1);
		if (term < BUFFER_SIZE)
			break ;
	}
	return (process_return(buffer, temp_str));
}

char	*get_next_line(int fd)
{
	static char	*temp_str;
	char		*buffer;

	if (!temp_str)
		temp_str = NULL;
	buffer = NULL;
	buffer = ft_calloc(1, 1);
	if (fd < 0 || BUFFER_SIZE <= 0 || !buffer)
	{
		free_all(&buffer, &temp_str);
		return (buffer);
	}
	if (temp_str)
		buffer = ft_strjoinfree(&buffer, &temp_str);
	if (search_next_line(&buffer, &temp_str, fd) == -1)
		free_all(&buffer, &temp_str);
	else if (temp_str && temp_str[0] == '\0')
		free_all(&temp_str, &temp_str);
	return (buffer);
}
