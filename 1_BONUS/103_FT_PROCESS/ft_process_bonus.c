/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:17:22 by lumugot           #+#    #+#             */
/*   Updated: 2025/08/11 18:36:27 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static inline void	ft_hit_parse(t_mlx_obj *mobj, int i[2],
	t_scene *s, const t_rules *r)
{
	t_obj	*hit;

	hit = ft_hit_nearest_obj(s->ray, s->objects);
	if (hit)
		return (ft_put_color(mobj, *i, *(i + 1),
				r->coloration(s->ray, hit, s, r)));
	if (r->coloration == ft_unicorn)
		return (ft_put_color(mobj, *i, *(i + 1), 0xdc96ff));
	if (r->coloration == ft_color_virus)
		return (ft_put_color(mobj, *i, *(i + 1), ft_rand()));
	if (r->coloration == ft_color_chill)
		return (ft_put_color(mobj, *i, *(i + 1), 0xcffff9));
	if (r->coloration == ft_color_error)
		return (ft_put_color(mobj, *i, *(i + 1),
				0xff0000 + 255 * (ft_rand() % 2)));
	ft_put_color(mobj, *i, *(i + 1), 0);
}

static void	ft_process_one_pixel(t_mlx_obj *mobj, t_scene *s,
	const t_rules *r, const t_vec cam_vectors[3])
{
	t_vec	ray_moves[2];
	t_vec	ray_move;

	ft_vec_scale(ray_moves[0], cam_vectors[0],
		((double)s->coords[0] / WIDTH) - 0.5);
	ft_vec_scale(ray_moves[1], cam_vectors[1],
		-(((double)s->coords[1] / HEIGHT) - 0.5));
	ft_vec_add(ray_move, ray_moves[0], ray_moves[1]);
	ft_vec_add(s->ray[0], s->camera.pos, ray_move);
	ft_vec_sub(s->ray[1], s->ray[0], cam_vectors[2]);
	ft_vec_norm(s->ray[1], s->ray[1]);
	ft_hit_parse(mobj, s->coords, s, r);
}

static inline void	ft_progbar(char reset)
{
	static unsigned int			prog = -1;
	static const unsigned int	max = HEIGHT * WIDTH;

	if (reset)
		prog = -1;
	else
	{
		printf("\r\e[94;7mR\e[0m%d%%\e[32;1m\e[0m    ",
			(unsigned int)(((double)++prog / max) * 100));
		fflush(stdout);
	}
}

static void	ft_calculate_pixels(t_mlx_obj *mobj, t_scene *s,
	const t_rules *r, const t_vec cam_vectors[3])
{
	s->coords[1] = 0;
	while (s->coords[1] < HEIGHT)
	{
		s->coords[0] = 0;
		while (s->coords[0] < WIDTH)
		{
			ft_progbar(0);
			ft_process_one_pixel(mobj, s, r, cam_vectors);
			s->coords[0] += r->pixel_cross;
		}
		s->coords[1] += r->pixel_cross;
	}
	ft_putstr_fd("\r\e[94;7mR\e[0m100%\e[32;1mOK\e[0m", 1);
	ft_progbar(1);
}

void	ft_process(t_mlx_obj *mobj,
	t_scene *s, const t_rules *r)
{
	t_vec	cam_vectors[3];

	ft_init_cam_vectors(cam_vectors, s);
	ft_calculate_pixels(mobj, s, r, cam_vectors);
}
