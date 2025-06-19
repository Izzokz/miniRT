/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:28:46 by lumugot           #+#    #+#             */
/*   Updated: 2024/11/05 07:48:40 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

size_t	ft_strlen(const char *str);
size_t	ft_line_len(const char *str);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strchr(const char *str, char c);
char	*ft_read_and_fill(int fd, char *buffer, char *stash);
char	*ft_copy_stay(char *str);
char	*ft_extract_line(char *str);
char	*get_next_line(int fd);

#endif
