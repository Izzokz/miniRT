/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:37:41 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/25 11:25:17 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

size_t	my_strlen(const char *str);
size_t	ft_line_len(const char *str);
char	*ft_strjoin_buf(char *s1, char *s2);
int		ft_strchr_endl(const char *str, char c);
char	*ft_read_and_fill(int fd, char *buffer, char *stash);
char	*ft_copy_stay(char *str);
char	*ft_extract_line(char *str);
char	*get_next_line(int fd);

#endif
