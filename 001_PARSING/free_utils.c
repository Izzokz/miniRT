/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:07:52 by lumugot           #+#    #+#             */
/*   Updated: 2025/07/04 15:02:28 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

void	free_tab(char **tab)
{
	int	iter;

	iter = 0;
	while (tab[iter])
	{
		free(tab[iter]);
		iter++;
	}
	free(tab);
}

void	free_objects(t_obj *obj)
{
    t_obj	*tmp;

    while (obj)
    {
        tmp = obj->next;
        if (obj->params)
            free(obj->params);
        free(obj);
        obj = tmp;
    }
}

void	free_lights(t_light *lights)
{
    t_light	*tmp;

    while (lights)
    {
        tmp = lights->next;
        free(lights);
        lights = tmp;
    }
}

void	free_scene(t_scene *scene)
{
	if (scene)
	{
		free_lights(scene->lights);
		free_objects(scene->objects);
	}
}
