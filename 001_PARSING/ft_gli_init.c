/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gli_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhen-cl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 08:36:14 by kzhen-cl          #+#    #+#             */
/*   Updated: 2025/07/07 08:43:16 by kzhen-cl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

inline void	ft_gli_unlock(t_vec dir, char gli[2])
{
	double					len;
	static int				a = 0;

	if (fabs(ft_vec_dot(dir, g_up)) < .99999)
		return ;
	++a;
	printf("Lock Found %d.\n", a);
	if (fabs(*dir) < fabs(*(dir + 2)))
		*dir += .001;
	else
		*(dir + 2) += .001;
	len = sqrt(*dir * *dir + *(dir + 1) * *(dir + 1)
		+ *(dir + 2) * *(dir + 2));
	if (len > 0)
		ft_new_vec(dir, *dir / len, *(dir + 1) / len, *(dir + 2) / len);
	*gli = 1;
	if (fabs(*dir) < fabs(*(dir + 2)))
		*(gli + 1) = 0;
	else
		*(gli + 1) = 2;
}

inline void	ft_gli_realign(t_vec dir, char gli[2])
{
	double	len;

	if (!*gli)
		return;
	if (*(gli + 1) == 0)
		*dir -= .001;
	else if (*(gli + 2) == 2)
		*(dir + 2) -= .001;
	len = sqrt(*dir * *dir + *(dir + 1) * *(dir + 1)
		+ *(dir + 2) * *(dir + 2));
	if (len > 0)
		ft_new_vec(dir, *dir / len, *(dir + 1) / len, *(dir + 2) / len);
	*gli = 0;
}

inline void	ft_gli_init(t_vec dir, t_gl_info *gli)
{
	gli->occured = 0;
	gli->axis = 0;
	gli->unlock = ft_gli_unlock;
	gli->realign = ft_gli_realign;
	gli->unlock(dir, (char *)gli);
}
