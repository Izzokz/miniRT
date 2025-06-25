/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:20:20 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/25 20:33:58 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

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

void	free_lights(t_list *lights)
{
    t_list	*tmp;

    while (lights)
    {
        tmp = lights->next;
        if (lights->content)
            free(lights->content);
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

int	main(int argc, char **argv)
{
    t_scene	scene;

    if (check_arg(argc, argv) == PARSE_KO)
        return (PARSE_KO);
    if (parse_scene(argv[1], &scene) == PARSE_KO)
        return (PARSE_KO);
    ft_putendl_fd("\033[1;32mParsing successful!\033[0m", 1);
    free_scene(&scene);
    return (PARSE_OK);
}
