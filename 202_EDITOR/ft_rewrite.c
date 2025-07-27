/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rewrite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:25:01 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/25 10:25:03 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline char	rewrite_sphere2(char **tokens, t_vec tmp_v, t_color tmp_c)
{
	if (!ft_sequals(tokens[0], "'")
		&& parse_vec3(tokens[0], tmp_v) == PARSE_KO)
	{
		print_error("Invalid vector for sphere !");
		return (PARSE_KO);
	}
	if (!ft_sequals(tokens[2], "'")
		&& parse_color(tokens[2], tmp_c) == PARSE_KO)
	{
		print_error("Invalid color for sphere !");
		return (PARSE_KO);
	}
	return (PARSE_OK);
}

char	rewrite_sphere(t_obj *obj, char **tokens)
{
	t_vec	tmp_v;
	t_color	tmp_c;
	double	tmp_d;

	if (!tokens[0] || !tokens[1] || !tokens[2] || tokens[3])
	{
		print_error("Invalid sphere format: "
			"sp <pos x,y,z> <diameter> <color r,g,b>");
		return (PARSE_KO);
	}
	if (rewrite_sphere2(tokens, tmp_v, tmp_c) == PARSE_KO)
		return (PARSE_KO);
	if (!ft_sequals(tokens[1], "'"))
		tmp_d = ft_atod(tokens[1]);
	if (!ft_sequals(tokens[0], "'"))
		ft_memcpy(obj->params, tmp_v, sizeof(t_vec));
	if (!ft_sequals(tokens[1], "'"))
		*(obj->params + 3) = tmp_d;
	if (!ft_sequals(tokens[2], "'"))
		ft_memcpy(obj->color, tmp_c, sizeof(t_color));
	return (PARSE_OK);
}

static inline char	rewrite_plane2(char **tokens, t_vec tmp_v[2])
{
	if (!ft_sequals(tokens[0], "'")
		&& parse_vec3(tokens[0], *tmp_v) == PARSE_KO)
	{
		print_error("Invalid vector for plane !");
		return (PARSE_KO);
	}
	if (!ft_sequals(tokens[1], "'"))
	{
		if (parse_vec3(tokens[1], *(tmp_v + 1)) == PARSE_KO)
		{
			print_error("Invalid vector for plane !");
			return (PARSE_KO);
		}
		if (**(tmp_v + 1) == 0 && *(*(tmp_v + 1) + 1) == 0
			&& *(*(tmp_v + 1) + 2) == 0)
		{
			print_error("Plane orientation vector cannot be null");
			return (PARSE_KO);
		}
	}
	return (PARSE_OK);
}

char	rewrite_plane(t_obj *obj, char **tokens)
{
	t_vec	tmp_v[2];
	t_color	tmp_c;

	if (!tokens[0] || !tokens[1] || !tokens[2] || tokens[3])
	{
		print_error("Invalid plane format: "
			"pl <pos x,y,z> <normal a,b,c> <color r,g,b>");
		return (PARSE_KO);
	}
	if (rewrite_plane2(tokens, tmp_v) == PARSE_KO)
		return (PARSE_KO);
	if (!ft_sequals(tokens[2], "'")
		&& parse_color(tokens[2], tmp_c) == PARSE_KO)
	{
		print_error("Invalid color for plane !");
		return (PARSE_KO);
	}
	if (!ft_sequals(tokens[0], "'"))
		ft_memcpy(obj->params, tmp_v, sizeof(t_vec));
	if (!ft_sequals(tokens[1], "'"))
		ft_memcpy(obj->params + 3, tmp_v + 1, sizeof(t_vec));
	if (!ft_sequals(tokens[2], "'"))
		ft_memcpy(obj->color, tmp_c, sizeof(t_color));
	return (PARSE_OK);
}
