/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_edit_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:18:25 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/08/10 19:46:57 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

	if (!*tokens || !*(tokens + 1) || *(tokens + 2))
	{
		print_error("Invalid light format: "
			"L <pos x,y,z> <ratio>");
		return (PARSE_KO);
	}
	if (rewrite_light2(tokens, tmp_v, &tmp_d) == PARSE_KO)
		return (PARSE_KO);
	if (!ft_sequals(*tokens, "'"))
		ft_memcpy(light->pos, tmp_v, sizeof(t_vec));
	if (!ft_sequals(*(tokens + 1), "'"))
		light->brightness = tmp_d;
	light->is_set = 1;
	return (PARSE_OK);
}

void	ft_edit_light(t_mlx_obj *mobj, t_scene *scene,
	t_rules *rules)
{
	char	*rewrite;
	char	**tokens;
	char	status;

	printf("\nL\t%f,%f,%f\t%f\n", *scene->light.pos,
		*(scene->light.pos + 1), *(scene->light.pos + 2),
		scene->light.brightness);
	explain_editor();
	rewrite = get_next_line(0);
	if (!rewrite && write(1, "^D\n", 3))
		return ;
	tokens = ft_split_space(rewrite);
	free(rewrite);
	if (!tokens)
	{
		ft_putstr_fd("Malloc failed\n", 2);
		return ;
	}
	status = rewrite_light(&scene->light, tokens);
	free_tab(tokens);
	if (status == PARSE_OK)
		ft_mlx_img_update(mobj, scene, rules, 1);
}
