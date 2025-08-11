/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_editor_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:30:21 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/11 18:57:03 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EDITOR_BONUS_H
# define FT_EDITOR_BONUS_H

# define COL_MINT        0x98FF98
# define COL_PEACH       0xFFDAB9
# define COL_SKYBLUE     0x87CEEB

# define NB_OBJECT "\n\nEnter the number of the object to modify\n"
# define EX_CHANGE "Change the object's parameters as shown in the example\n"
# define EX_1 "Example (for a cylinder): 2,2,2 0,-1,0 1.7 2.4 255,255,255\n"
# define KEEP_PARAMS "Use ' to keep the original parameter\n"
# define EX_2 "Example (for the cylinder): 2,4,2 ' 1.7 ' 255,0,0\n\n"
# define SET_PARAMS "Set new params:\n"

void	ft_edit_light(t_mlx_obj *mobj, t_scene *scene, t_rules *rules);
void	ft_edit_ambient(t_mlx_obj *mobj, t_scene *scene, t_rules *rules);
char	rewrite_sphere(t_obj *obj, char **tokens);
char	rewrite_plane(t_obj *obj, char **tokens);
char	rewrite_cylinder(t_obj *obj, char **tokens);
char	rewrite_cone(t_obj *obj, char **tokens);
char	not_numeric_free(char *const s);
void	ft_open_editor(t_mlx_obj *mobj, t_scene *scene, t_rules *rules);

// editor_helper_bonus.c
void	ft_putstr_color(const char *str, int color);
void	explain_editor(void);

#endif
