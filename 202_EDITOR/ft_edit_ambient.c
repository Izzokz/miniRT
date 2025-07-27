/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_edit_ambient.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 10:46:49 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/27 10:46:50 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline char	rewrite_ambient2(char **tokens, double *tmp_d)
{
	if (!ft_sequals(*tokens, "'"))
	{
		*tmp_d = ft_atod(*tokens);
		if (*tmp_d < 0.0 || *tmp_d > 1.0)
		{
			print_error("Ambient light ratio must be in range [0.0,1.0]");
			return (PARSE_KO);
		}
	}
	return (PARSE_OK);
}

static inline char	rewrite_ambient(t_ambient *ambient, char **tokens)
{
	double	tmp_d;
	t_color	tmp_c;

	if (!tokens[0] || !tokens[1] || tokens[2])
	{
		print_error("Invalid ambient light format");
		return (PARSE_KO);
	}
	if (rewrite_ambient2(tokens, &tmp_d) == PARSE_KO)
		return (PARSE_KO);
	if (!ft_sequals(*(tokens + 1), "'")
		&& parse_color(tokens[1], tmp_c) != PARSE_OK)
	{
		print_error("Invalid ambient light color");
		return (PARSE_KO);
	}
	if (!ft_sequals(*tokens, "'"))
		ambient->ratio = tmp_d;
	if (!ft_sequals(*(tokens + 1), "'"))
		ft_memcpy(ambient->color, tmp_c, sizeof(t_color));
	return (PARSE_OK);
}

inline void	ft_edit_ambient(t_mlx_obj *mobj, t_scene *scene, t_rules *rules)
{
	char	*rewrite;
	char	**tokens;
	char	status;

	printf("A\t%f\t%d,%d,%d\n", scene->ambient_light.ratio,
		*scene->ambient_light.color, *(scene->ambient_light.color + 1),
		*(scene->ambient_light.color + 1));
	write(1, "Rewrite the ambient's parameters (w/o ID)\n", 42);
	write(1, "(you can skip parts with \"'\")\n", 30);
	rewrite = get_next_line(0);
	if (!rewrite)
		return ;
	tokens = ft_split_space(rewrite);
	free(rewrite);
	status = rewrite_ambient(&scene->ambient_light, tokens);
	free_tab(tokens);
	if (status == PARSE_OK)
		ft_mlx_img_update(mobj, scene, rules, 1);
}
