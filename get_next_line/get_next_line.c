/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:23:41 by lumugot           #+#    #+#             */
/*   Updated: 2024/11/06 17:46:44 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_and_fill(int fd, char *buffer, char *stash)
{
	int	read_char;

	read_char = 1;
	while ((!ft_strchr(stash, '\n')) && read_char > 0)
	{
		read_char = read(fd, buffer, BUFFER_SIZE);
		if (read_char <= 0)
			break ;
		buffer[read_char] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	if (read_char < 0 || (read_char == 0 && ft_strlen(stash) == 0))
	{
		free(stash);
		return (NULL);
	}
	return (stash);
}

char	*ft_extract_line(char *str)
{
	int		index;
	int		len_n;
	char	*stock;

	if (!str)
		return (NULL);
	index = 0;
	len_n = ft_line_len(str);
	stock = malloc(sizeof(char) * (len_n + 1));
	if (!stock)
		return (NULL);
	while (str[index] && index < len_n)
	{
		stock[index] = str[index];
		index++;
	}
	stock[index] = '\0';
	return (stock);
}

char	*ft_copy_stay(char *str)
{
	int		index;
	int		len;
	char	*save;

	if (!str)
		return (NULL);
	index = 0;
	len = ft_line_len(str);
	save = malloc(sizeof(char) * ((ft_strlen(str) - len) + 1));
	if (!save)
	{
		free(str);
		return (NULL);
	}
	while (str[len])
	{
		save[index] = str[len];
		index++;
		len++;
	}
	save[index] = '\0';
	free(str);
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
	{
		stash = malloc(1);
		stash[0] = 0;
	}
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	stash = ft_read_and_fill(fd, buffer, stash);
	free(buffer);
	line = ft_extract_line(stash);
	if (!line)
	{
		free(stash);
		return (NULL);
	}
	stash = ft_copy_stay(stash);
	return (line);
}
