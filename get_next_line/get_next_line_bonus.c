/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:26:19 by lumugot           #+#    #+#             */
/*   Updated: 2024/11/06 17:42:29 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*stash[1024];
	char		*line;
	char		*buffer;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	stash[fd] = ft_read_and_fill(fd, buffer, stash[fd]);
	free(buffer);
	if (!stash[fd])
		return (NULL);
	line = ft_extract_line(stash[fd]);
	if (!line)
	{
		free(stash[fd]);
		return (NULL);
	}
	stash[fd] = ft_copy_stay(stash[fd]);
	return (line);
}
