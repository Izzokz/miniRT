/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:20:20 by lumugot           #+#    #+#             */
/*   Updated: 2025/07/26 12:55:49 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_vec(const char *name, t_vec vec)
{
	printf("\t%s: (%.2f, %.2f, %.2f)\n", name, vec[0], vec[1], vec[2]);
}

void	print_color(const char *name, t_color color)
{
	printf("\t%s: (%u, %u, %u)\n", name, color[0], color[1], color[2]);
}

void print_all_data(t_scene *scene)
{
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
	light = scene->lights;
	if (!light)
		printf("\tNo lights in scene.\n");
	i = 0;
	while (light)
	{
		printf("  Light %d:\n", i++);
		print_vec("  Position", light->pos);
		printf("\t  Brightness: %.2f\n", light->brightness);
		print_color("  Color", light->color);
		light = light->next;
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
		if (obj->hit == ft_hit_s)
		{
			printf("\tType: Sphere\n");
			print_vec("Center", obj->params);
			printf("\tDiameter: %.2f\n", obj->params[3]);
		}
		else if (obj->hit == ft_hit_p)
		{
			printf("\tType: Plane\n");
			print_vec("Point", obj->params);
			print_vec("Normal", obj->params + 3);
		}
		else if (obj->hit == ft_hit_c)
		{
			printf("\tType: Cylinder\n");
			print_vec("Center", obj->params);
			print_vec("Axis", obj->params + 3);
			printf("\tDiameter: %.2f\n", obj->params[6]);
			printf("\tHeight: %.2f\n", obj->params[7]);
		}
		if (obj->hit == ft_hit_cone)
		{
			printf("\tType: Cone\n");
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

static inline void	save_cam(t_camera *save, t_scene *scene)
{
	*save = (t_camera){
	{
		*scene->camera.pos,
		*(scene->camera.pos + 1),
		*(scene->camera.pos + 2)
	},
	{
		*scene->camera.orientation,
		*(scene->camera.orientation + 1),
		*(scene->camera.orientation + 2)
	},
		scene->camera.fov, 1};
	ft_set_const_cam(save);
}

static inline void	init_world(t_scene *scene)
{
	ft_new_vec(scene->_up, 0, 1, 0);
	ft_cpy_vec(scene->_forward, scene->camera.orientation);
	ft_vec_cross(scene->_right, scene->_forward, scene->_up);
	scene->_pitch = asin(*(scene->camera.orientation + 1));
}

int	main(int argc, char **argv)
{
	t_scene		scene;
	t_camera	save;

	if (check_arg(argc, argv) == PARSE_KO)
		return (PARSE_KO);
	if (parse_scene(argv[1], &scene) == PARSE_KO)
	{
		free_scene(&scene);
		return (PARSE_KO);
	}
	else
	{
		save_cam(&save, &scene);
		init_world(&scene);
		ft_putendl_fd("\033[1;32mParsing successful!\033[0m", 1);
		ft_mlx_loop(ft_mlx_obj_init(), &scene);
	}
	free_scene(&scene);
	return (PARSE_OK);
}
