/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 10:07:35 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/09 10:09:45 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "tuple.h"

static const char	*get_type(const t_shape *self)
{
	(void)self;
	return ("plane");
}

static void	intersect(const t_shape *self, t_xs *xs, t_ray ray)
{
	double	t;

	if (deq(ray.dir.arr[Y], 0))
		return ;
	t = -ray.orig.arr[Y] / ray.dir.arr[Y];
	xs->xs[xs->count].t = t;
	xs->xs[xs->count++].shape = (t_shape *)self;
}

static t_tuple	local_normal_at(const t_shape *self, t_tuple p)
{
	(void)self;
	(void)p;
	return (vector(0, 1, 0));
}

void	init_plane(t_plane *self, t_tuple coord, t_rgb rgb, t_tuple normal)
{
	init_shape(&self->base, PLANE, coord, rgb);
	self->normal = tuple_normalize(normal);
	self->base.transform = mat_translate(
			coord.arr[X],
			coord.arr[Y],
			coord.arr[Z]);
	self->base.get_type = get_type;
	self->base.intersect = intersect;
	self->base.local_normal_at = local_normal_at;
}
