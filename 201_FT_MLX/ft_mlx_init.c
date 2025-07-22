/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:59:00 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/17 14:50:16 by lumugot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static inline char	ft_mlx_win_img_init(t_mlx_obj *mobj)
{
	int	a;

	mobj->win_i = WIDTH;
	mobj->win_j = HEIGHT;
	mobj->win = mlx_new_window(mobj->mlx, mobj->win_i, mobj->win_j,
			"miniRT (AI)");
	if (!mobj->win)
	{
		ft_putendl_fd("MLXOBJ: mlx_new_window fail", 2);
		return (1);
	}
	mobj->img = mlx_new_image(mobj->mlx, mobj->win_i, mobj->win_j);
	if (!mobj->img)
	{
		ft_putendl_fd("MLXOBJ: mlx_new_image fail", 2);
		return (1);
	}
	mobj->img_data = mlx_get_data_addr(mobj->img,
			&mobj->bpp, &mobj->size_line, &a);
	return (0);
}

t_mlx_obj	*ft_mlx_obj_init(void)
{
	t_mlx_obj	*mobj;

	mobj = ft_calloc(1, sizeof(t_mlx_obj));
	if (!mobj)
	{
		ft_putendl_fd("MLXOBJ: malloc fail", 2);
		return (NULL);
	}
	mobj->mlx = mlx_init();
	if (!mobj->mlx)
	{
		ft_putendl_fd("MLXOBJ: mlx_init fail", 2);
		free(mobj);
		return (NULL);
	}
	if (ft_mlx_win_img_init(mobj))
	{
		ft_free_mlx_obj(mobj);
		return (NULL);
	}
	return (mobj);
}

void	ft_free_mlx_obj(t_mlx_obj *mobj)
{
	if (mobj->img)
		mlx_destroy_image(mobj->mlx, mobj->img);
	if (mobj->win)
		mlx_destroy_window(mobj->mlx, mobj->win);
	mlx_destroy_display(mobj->mlx);
	free(mobj->mlx);
	free(mobj);
}
