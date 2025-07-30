/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:20:20 by lumugot           #+#    #+#             */
/*   Updated: 2025/07/27 12:49:26 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	ft_vec_norm(scene->_right, scene->_right);
	scene->_pitch = asin(scene->_forward[1]);
	scene->_yaw = atan2(scene->_forward[2], scene->_forward[0]);
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
