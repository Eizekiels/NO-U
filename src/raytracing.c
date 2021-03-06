/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboucaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 20:11:06 by kboucaud          #+#    #+#             */
/*   Updated: 2018/04/28 21:06:43 by mguyout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void		ft_convert(t_rt *rt)
{
	if (rt->inter->mat->r > 1.0)
		rt->inter->mat->r = 1.0;
	if (rt->inter->mat->g > 1.0)
		rt->inter->mat->g = 1.0;
	if (rt->inter->mat->b > 1.0)
		rt->inter->mat->b = 1.0;
	rt->inter->mat->r = (int)(rt->inter->mat->r * 255);
	rt->inter->mat->g = (int)(rt->inter->mat->g * 255);
	rt->inter->mat->b = (int)(rt->inter->mat->b * 255);
}

void		ft_ray(t_rt *rt, int x, int y, int type)
{
	rt->tmp = rt->ray->dir;
	ft_check_object(rt);
	ft_convert(rt);
	if (type == 2)
		return ;
	put_pxl(rt->data, x, y, rt->inter->mat);
	put_pxl_base(rt->data, x, y, rt->inter->mat);
}

void		ft_ini_ray(t_rt *rt, double x, double y)
{
	rt->ray->dir = ft_sub_vect(ft_add_vect(rt->view->up_left,
	ft_mult_vect(rt->view->length * x / WIN_LEN, rt->cam->right)),
	ft_mult_vect(rt->view->height * y / WIN_HEIGHT, rt->cam->up));
	rt->ray->dir = ft_rotation(rt->ray->dir, rt->cam->rot);
	rt->ray->dir = ft_normalize(rt->ray->dir);
}

void		ft_raytracing(t_rt *rt)
{
	int			x;
	int			y;

	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_LEN)
		{
			rt->depth = 0;
			rt->lock = 0;
			ft_ini_ray(rt, x, y);
			ft_ray(rt, x, y, 1);
			rt->ray->o = rt->cam->pos;
		}
	}
}
