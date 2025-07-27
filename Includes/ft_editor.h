/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_editor.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:30:21 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/25 10:30:22 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EDITOR_H
# define FT_EDITOR_H

void	ft_edit_light(t_mlx_obj *mobj, t_scene *scene, t_rules *rules);
void	ft_edit_ambient(t_mlx_obj *mobj, t_scene *scene, t_rules *rules);
char	rewrite_sphere(t_obj *obj, char **tokens);
char	rewrite_plane(t_obj *obj, char **tokens);
char	rewrite_cylinder(t_obj *obj, char **tokens);
char	rewrite_cone(t_obj *obj, char **tokens);
char	not_numeric_free(char *s);
void	ft_open_editor(t_mlx_obj *mobj, t_scene *scene, t_rules *rules);

#endif
