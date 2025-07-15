/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:34:19 by lumugot           #+#    #+#             */
/*   Updated: 2025/07/04 15:45:26 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

int	fill_light_data(t_light *light, char **tokens)
{
	if (parse_vec3(tokens[1], light->pos) != PARSE_OK)
	{
		print_error("Invalid light position format");
		return (PARSE_KO);
	}
	light->brightness = ft_atod(tokens[2]);
	if (light->brightness < 0.0 || light->brightness > 1.0)
	{
		print_error("Light brightness ratio must be in range [0.0,1.0]");
		return (PARSE_KO);
	}
	if (parse_color(tokens[3], light->color) != PARSE_OK)
	{
		print_error("Invalid light color");
		return (PARSE_KO);
	}
	return (PARSE_OK);
}

static void	light_add_back(t_light **lst, t_light *new_light)
{
    t_light	*current;

    if (!lst || !new_light)
        return;
    if (!*lst)
    {
        *lst = new_light;
        return;
    }
    current = *lst;
    while (current->next)
        current = current->next;
    current->next = new_light;
}

int	parse_light(char **tokens, t_scene *scene)
{
    t_light	*light;

    if (ft_strncmp(tokens[0], "L", 2) != 0 || !tokens[1] || !tokens[2]
        || !tokens[3] || tokens[4])
    {
		print_error("Invalid light format: "
			"L <pos x,y,z> <ratio> <color r,g,b>");
		return (PARSE_KO);
    }
    light = malloc(sizeof(t_light));
    if (!light)
        return (MALLOC_FAILED);
    ft_memset(light, 0, sizeof(t_light));
    if (fill_light_data(light, tokens) != PARSE_OK)
    {
        free(light);
        return (PARSE_KO);
    }
    light_add_back(&scene->lights, light);
    return (PARSE_OK);
}
