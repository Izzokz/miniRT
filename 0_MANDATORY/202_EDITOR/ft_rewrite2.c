/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rewrite2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 09:52:40 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/27 09:52:41 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

char	rewrite_cylinder2(char **tokens, t_vec tmp_v[2], double tmp_d[2])
{
	if (!ft_sequals(tokens[0], "'")
		&& parse_vec3(tokens[0], *tmp_v) == PARSE_KO)
	{
		print_error("Invalid vector for cylinder !");
		return (PARSE_KO);
	}
	if (!ft_sequals(tokens[1], "'"))
	{
		if (parse_vec3(tokens[1], *(tmp_v + 1)) == PARSE_KO)
		{
			print_error("Invalid vector for cylinder !");
			return (PARSE_KO);
		}
		if (**(tmp_v + 1) == 0 && *(*(tmp_v + 1) + 1) == 0
			&& *(*(tmp_v + 1) + 2) == 0)
		{
			print_error("Cylinder orientation vector cannot be null");
			return (PARSE_KO);
		}
	}
	if (!ft_sequals(tokens[2], "'"))
		*tmp_d = ft_atod(tokens[2]);
	if (!ft_sequals(tokens[3], "'"))
		*(tmp_d + 1) = ft_atod(tokens[3]);
	return (PARSE_OK);
}

static inline char	bad_tokens_cylinder(char **tokens)
{
	if (!*tokens || !*(tokens + 1) || !*(tokens + 2)
		|| !*(tokens + 3) || !*(tokens + 4) || *(tokens + 5))
	{
		print_error("Invalid cylinder format: "
			"cy <pos> <normal> <diameter> <height> <color>");
		return (PARSE_KO);
	}
	if (**(tokens + 3) == '-')
	{
		print_error("Invalid height for cylinder !");
		return (PARSE_KO);
	}
	return (PARSE_OK);
}

char	rewrite_cylinder(t_obj *obj, char **tokens)
{
	t_vec	tmp_v[2];
	double	tmp_d[2];
	t_color	tmp_c;

	if (bad_tokens_cylinder(tokens)
		|| rewrite_cylinder2(tokens, tmp_v, tmp_d) == PARSE_KO)
		return (PARSE_KO);
	if (!ft_sequals(tokens[4], "'")
		&& parse_color(tokens[4], tmp_c) == PARSE_KO)
	{
		print_error("Invalid color for cylinder !");
		return (PARSE_KO);
	}
	if (!ft_sequals(tokens[0], "'"))
		ft_memcpy(obj->params, tmp_v, sizeof(t_vec));
	if (!ft_sequals(tokens[1], "'"))
		ft_memcpy(obj->params + 3, tmp_v + 1, sizeof(t_vec));
	if (!ft_sequals(tokens[2], "'"))
		*(obj->params + 6) = *tmp_d;
	if (!ft_sequals(tokens[3], "'"))
		*(obj->params + 7) = *(tmp_d + 1);
	if (!ft_sequals(tokens[4], "'"))
		ft_memcpy(obj->color, tmp_c, sizeof(t_color));
	return (PARSE_OK);
}
