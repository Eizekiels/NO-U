/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflexion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguyout <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 19:15:22 by mguyout           #+#    #+#             */
/*   Updated: 2018/04/28 19:16:02 by mguyout          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

t_coo	ft_reflexion(t_rt *rt)
{
	t_coo newray;
	double dotp;

	rt->inter->angle->dir = ft_normalize(rt->inter->angle->dir);
	rt->ray->dir = ft_normalize(rt->ray->dir);
	dotp = scal(rt->ray->dir, rt->inter->angle->dir);
	newray.x = rt->ray->dir.x - 2 * dotp * rt->inter->angle->dir.x;
	newray.y = rt->ray->dir.y - 2 * dotp * rt->inter->angle->dir.y;
	newray.z = rt->ray->dir.z - 2 * dotp * rt->inter->angle->dir.z;
	newray = ft_normalize(newray);
	return (newray);
}

void	ft_reflexion_ray(t_rt *rt)
{
	t_material color;
	double reflex;

	reflex = rt->inter->reflex;
	reflexion_depth(rt); // calcul du rayon reflechi final
	if (rt->inter->dst <= 0.01)
		rt->inter->dst = 0;
	if (rt->inter->dst != MAX)
	{

		color.r = rt->inter->col->r;
		color.g = rt->inter->col->g;
		color.b = rt->inter->col->b;
		ft_get_point(rt);
		rt->ray->o = rt->cam->pos;
		rt->ray->dir = rt->inter->point;
		rt->ray->dir = ft_normalize(rt->ray->dir);
		rt->light = rt->start->lgh;
		if (rt->inter->reflex <= 0) // si reflexion infini alors on affiche noir
		{
			ft_get_light(rt);
	//		rt->inter->mat->r = (((float)(reflex) * color.r) + rt->inter->mat->r) / 2;
	//		rt->inter->mat->g = (((float)(reflex) * color.g) + rt->inter->mat->g) / 2;
	//		rt->inter->mat->b = (((float)(reflex) * color.b) + rt->inter->mat->b) / 2;
	//		ft_check_expose(rt->inter->mat, 1.0);
		}
	}
}

void	reflexion_depth(t_rt *rt)
{
	while (rt->inter->reflex > 0 && rt->depth < 3)
	{
		if (rt->inter->dst <= 0.01)
			rt->inter->dst = 0;
		if (rt->inter->dst != MAX)
		{
			ft_get_point(rt);
			rt->depth++;
			rt->ray->dir = ft_reflexion(rt);
			rt->ray->o = rt->inter->point;
			rt->inter->dst = MAX;
			rt->inter->reflex = 0;
			check_forms(rt, 0);
		}
	}
}
