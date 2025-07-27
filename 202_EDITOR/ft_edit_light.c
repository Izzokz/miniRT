/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_edit_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:18:25 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/27 12:18:26 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline void	ft_print_light(t_light *light)
{
	printf("L\t%f,%f,%f\t%f\t%d,%d,%d\n", *light->pos, *(light->pos + 1),
		*(light->pos + 2), light->brightness, *light->color,
		*(light->color + 1), *(light->color + 2));
}

static inline char	rewrite_light2(char **tokens, t_vec tmp_v, double *tmp_d)
{
	if (!ft_sequals(*tokens, "'")
		&& parse_vec3(tokens[0], tmp_v) == PARSE_KO)
	{
		print_error("Invalid light position format");
		return (PARSE_KO);
	}
	if (!ft_sequals(*(tokens + 1), "'"))
	{
		*tmp_d = ft_atod(tokens[1]);
		if (*tmp_d < 0.0 || *tmp_d > 1.0)
		{
			print_error("Light brightness ratio must be in range [0.0,1.0]");
			return (PARSE_KO);
		}
	}
	return (PARSE_OK);
}

static inline char	rewrite_light(t_light *light, char **tokens)
{
	t_vec	tmp_v;
	double	tmp_d;
	t_color	tmp_c;

	if (!*tokens || !*(tokens + 1) || !*(tokens + 2) || *(tokens + 3))
	{
		print_error("Invalid light format: "
			"L <pos x,y,z> <ratio> <color r,g,b>");
		return (PARSE_KO);
	}
	if (rewrite_light2(tokens, tmp_v, &tmp_d) == PARSE_KO)
		return (PARSE_KO);
	if (!ft_sequals(*(tokens + 2), "'")
		&& parse_color(tokens[2], tmp_c) != PARSE_OK)
	{
		print_error("Invalid light color");
		return (PARSE_KO);
	}
	if (!ft_sequals(*tokens, "'"))
		ft_memcpy(light->pos, tmp_v, sizeof(t_vec));
	if (!ft_sequals(*(tokens + 1), "'"))
		light->brightness = tmp_d;
	if (!ft_sequals(*(tokens + 2), "'"))
		ft_memcpy(light->color, tmp_c, sizeof(t_color));
	return (PARSE_OK);
}

static inline void	ft_edit_light2(int i, t_mlx_obj *mobj,
	t_scene *scene, t_rules *rules)
{
	t_light	*edit;
	char	*rewrite;
	char	**tokens;
	char	status;

	edit = scene->lights;
	while (--i >= 0)
		edit = edit->next;
	write(1, "\n", 1);
	ft_print_light(edit);
	write(1, "Rewrite the light's parameters (w/o ID)\n", 40);
	write(1, "(you can skip parts with \"'\")\n", 30);
	rewrite = get_next_line(0);
	if (!rewrite)
		return ;
	tokens = ft_split_space(rewrite);
	free(rewrite);
	if (!tokens)
		return ((void)ft_putstr_fd("Malloc failed\n", 2));
	status = rewrite_light(edit, tokens);
	free_tab(tokens);
	if (status == PARSE_OK)
		ft_mlx_img_update(mobj, scene, rules, 1);
}

void	ft_edit_light(t_mlx_obj *mobj, t_scene *scene,
	t_rules *rules)
{
	char	*answer;
	t_light	*current;
	int		i;
	int		ans_i;

	current = scene->lights;
	i = -1;
	write(1, "\n", 1);
	while (current)
	{
		printf("%d\t- ", ++i);
		ft_print_light(current);
		current = current->next;
	}
	write(1, "\nSelect a light to edit\n", 24);
	answer = get_next_line(0);
	if (!answer)
		return ;
	if (not_numeric_free(answer))
		return ((void)printf("\e[31mInvalid.\n\e[0m"));
	ans_i = ft_atoi(answer);
	free(answer);
	if (ans_i < 0 || ans_i > i)
		return ((void)printf("\e[31mInvalid.\n\e[0m"));
	ft_edit_light2(ans_i, mobj, scene, rules);
}
