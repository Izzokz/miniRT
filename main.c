/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:20:20 by lumugot           #+#    #+#             */
/*   Updated: 2025/06/26 12:05:40 by lumugot          ###   ########.fr       */
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

static void	print_vec(const char *name, t_vec vec)
{
    printf("\t%s: (%.2f, %.2f, %.2f)\n", name, vec[0], vec[1], vec[2]);
}

static void	print_color(const char *name, t_color color)
{
    printf("\t%s: (%u, %u, %u)\n", name, color[0], color[1], color[2]);
}

void	print_all_data(t_scene *scene)
{
    t_list	*light_node;
    t_light	*light;
    t_obj	*obj;
    int		i;

    printf("--- SCENE DATA ---\n\n");
    printf("Ambient Light:\n");
    if (scene->ambient_light.is_set)
    {
        printf("\tRatio: %.2f\n", scene->ambient_light.ratio);
        print_color("Color", scene->ambient_light.color);
    }
    else
        printf("\tNot Set\n");
    printf("\n");
    printf("Camera:\n");
    if (scene->camera.is_set)
    {
        print_vec("Position", scene->camera.pos);
        print_vec("Orientation", scene->camera.orientation);
        printf("\tFOV: %.1f\n", scene->camera.fov);
    }
    else
        printf("\tNot Set\n");
    printf("\n");
    printf("Lights:\n");
    light_node = scene->lights;
    if (!light_node)
        printf("\tNo lights in scene.\n");
    i = 0;
    while (light_node)
    {
        light = (t_light *)light_node->content;
        printf("  Light %d:\n", i++);
        print_vec("  Position", light->pos);
        printf("\t  Brightness: %.2f\n", light->brightness);
        print_color("  Color", light->color);
        light_node = light_node->next;
    }
    printf("\n");
    printf("Objects:\n");
    obj = scene->objects;
    if (!obj)
        printf("\tNo objects in scene.\n");
    i = 0;
    while (obj)
    {
        printf("  Object %d:\n", i++);
        if (obj->type == 's')
        {
            printf("\tType: Sphere\n");
            print_vec("Center", obj->params);
            printf("\tDiameter: %.2f\n", obj->params[3]);
        }
        if (obj->type == 'p')
        {
            printf("\tType: Plane\n");
            print_vec("Point", obj->params);
            print_vec("Normal", obj->params + 3);
        }
        if (obj->type == 'c')
        {
            printf("\tType: Cylinder\n");
            print_vec("Center", obj->params);
            print_vec("Axis", obj->params + 3);
            printf("\tDiameter: %.2f\n", obj->params[6]);
            printf("\tHeight: %.2f\n", obj->params[7]);
        }
        print_color("Color", obj->color);
        obj = obj->next;
    }
    printf("\n--- END SCENE DATA ---\n");
}


int	main(int argc, char **argv)
{
    t_scene	scene;

    if (check_arg(argc, argv) == PARSE_KO)
        return (PARSE_KO);
    if (parse_scene(argv[1], &scene) == PARSE_KO)
        return (PARSE_KO);
    ft_putendl_fd("\033[1;32mParsing successful!\033[0m", 1);
	print_all_data(&scene);
    free_scene(&scene);
    return (PARSE_OK);
}
