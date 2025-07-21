/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:30:03 by lumugot           #+#    #+#             */
/*   Updated: 2025/07/21 12:19:40 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

//ft_pos_val.c
double	ft_pos_val(const double val);

//split_utils.c
char	**ft_split_space(const char *s);

//ft_swap.c
void	ft_swap(double *a, double *b);

//check_params.c
int		is_valid_params(const char *str);

#endif
