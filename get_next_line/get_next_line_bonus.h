/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:28:46 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/23 16:01:28 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include "../Libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

size_t	ft_line_len(const char *str);
char	*ft_read_and_fill(int fd, char *buffer, char *stash);
char	*ft_copy_stay(char *str);
char	*ft_extract_line(char *str);
char	*get_next_line(int fd);

#endif
