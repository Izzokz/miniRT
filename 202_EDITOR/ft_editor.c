/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_editor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:27:14 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/25 10:27:14 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline void	ft_print_object(t_obj *o)
{
	if (o->hit == ft_hit_s)
		printf("sp\t%f,%f,%f\t%f\t%d,%d,%d\n", *o->params, *(o->params + 1),
			*(o->params + 2), *(o->params + 3), *o->color, *(o->color + 1),
			*(o->color + 2));
	else if (o->hit == ft_hit_c)
		printf("cy\t%f,%f,%f\t%f,%f,%f\t%f\t%f\t%d,%d,%d\n", *o->params,
			*(o->params + 1), *(o->params + 2), *(o->params + 3),
			*(o->params + 4), *(o->params + 5), *(o->params + 6),
			*(o->params + 7), *o->color, *(o->color + 1), *(o->color + 2));
	else if (o->hit == ft_hit_c3)
		printf("DEPRACATED c3");
	else if (o->hit == ft_hit_cone)
		printf("co\t%f,%f,%f\t%f,%f,%f\t%f\t%f\t%d,%d,%d\n", *o->params,
			*(o->params + 1), *(o->params + 2), *(o->params + 3),
			*(o->params + 4), *(o->params + 5), *(o->params + 6),
			*(o->params + 7), *o->color, *(o->color + 1), *(o->color + 2));
	else if (o->hit == ft_hit_p)
		printf("pl\t%f,%f,%f\t%f,%f,%f\t%d,%d,%d\n", *o->params,
			*(o->params + 1), *(o->params + 2), *(o->params + 3),
			*(o->params + 4), *(o->params + 5), *o->color, *(o->color + 1),
			*(o->color + 2));
}

static inline char	ft_edit_object3(char (*hit)(const t_obj *, t_ray),
	t_obj *edit, char **tokens)
{
	if (hit == ft_hit_s)
		return (rewrite_sphere(edit, tokens));
	else if (hit == ft_hit_p)
		return (rewrite_plane(edit, tokens));
//	else if (hit == ft_hit_c)
//		status = rewrite_cylinder(edit, tokens);
//	else if (hit == ft_hit_c3) // WON'T EXIST (CUBES NOT OK)
//		status = rewrite_cube(edit, tokens);
//	else if (hit == ft_hit_cone)
//		status = rewrite_cone(edit, tokens);
	return (1);
}

static inline void	ft_edit_object2(int i, t_mlx_obj *mobj,
	t_scene *scene, t_rules *rules)
{
	t_obj	*edit;
	char	*rewrite;
	char	**tokens;
	char	status;

	edit = scene->objects;
	while (--i >= 0)
		edit = edit->next;
	write(1, "\n", 1);
	ft_print_object(edit);
	write(1, "Rewrite the object's parameters (w/o ID)\n", 41);
	write(1, "(you can skip parts with \"'\")\n", 30);
	rewrite = get_next_line(0);
	if (!rewrite)
		return ;
	tokens = ft_split_space(rewrite);
	free(rewrite);
	if (!tokens)
		return ((void)ft_putstr_fd("Malloc failed\n", 2));
	status = ft_edit_object3(edit->hit, edit, tokens);
	free_tab(tokens);
	if (status == PARSE_OK)
		ft_mlx_img_update(mobj, scene, rules, 1);
}

static inline void	ft_edit_object(t_mlx_obj *mobj, t_scene *scene,
	t_rules *rules)
{
	char	*answer;
	t_obj	*current;
	int		i;
	int		ans_i;

	current = scene->objects;
	i = -1;
	write(1, "\n", 1);
	while (current)
	{
		printf("%d\t-", ++i);
		ft_print_object(current);
		current = current->next;
	}
	write(1, "\nSelect an object to edit\n", 26);
	answer = get_next_line(0);
	if (!answer)
		return ;
	if (not_numeric_free(answer))
		return ((void)printf("\e[31mInvalid.\n\e[0m"));
	ans_i = ft_atoi(answer);
	free(answer);
	if (ans_i < 0 || ans_i > i)
		return ((void)printf("\e[31mInvalid.\n\e[0m"));
	ft_edit_object2(ans_i, mobj, scene, rules);
}

void	ft_open_editor(t_mlx_obj *mobj, t_scene *scene, t_rules *rules)
{
	char	*answer;

	ft_putstr_fd("\nEDITOR\n\t- 0 OBJECTS\n\t- 1 LIGHTS\n\t- 2 AMBIENT\n", 1);
	answer = get_next_line(0);
	if (!answer)
		return ;
	if (ft_sequals(answer, "0\n"))
		ft_edit_object(mobj, scene, rules);
//	else if (ft_sequals(answer, "1\n"))
//		ft_edit_light(mobj, scene, rules);
//	else if (ft_sequals(answer, "2\n"))
//		ft_edit_ambient(mobj, scene, rules);
	free(answer);
}
