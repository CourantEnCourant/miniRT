/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xs.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 21:01:29 by weizhang          #+#    #+#             */
/*   Updated: 2026/08/08 21:01:43 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "minirt.h"

void	add_xs(t_xs *xs, const t_shape *shape, double t)
{
	if (t < 0)
		return ;
	if (xs->best.shape && xs->best.t <= t)
		return ;
	xs->best.t = t;
	xs->best.shape = (t_shape *)shape;
}

void	intersect_world(t_xs *xs, const t_ray ray, const t_conf *conf)
{
	size_t	i;
	t_shape	*shape;
	t_ray	local_ray;

	xs->best.t = -1;
	xs->best.shape = NULL;
	i = 0;
	while (i < conf->shapes->len)
	{
		shape = conf->shapes->arr[i++];
		local_ray = transform(ray, &shape->transform_inv);
		shape->intersect(shape, xs, local_ray);
	}
}
