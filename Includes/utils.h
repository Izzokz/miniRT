/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:30:03 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/26 12:49:09 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_C
# define UTILS_C

//split_utils.c
static inline int	count_str(char const *str);
static inline char	*catch_substring(char const *s, int begin, int ending);
static inline char	addition_manager(char **tab, const char *s,
	int *const istart, int j[1]);
char				**ft_split_space(const char *s);

# include "miniRT.h"

#endif