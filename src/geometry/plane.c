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

#include <math.h>
#include "minirt.h"
#include "tuple.h"

static const char	*get_type(const t_shape *self)
{
	(void)self;
	return ("plane");
}

static void intersect(const t_shape *self, t_xs *xs, t_ray ray)
{
	double	t;

	ray = transform(ray, mat_inv(self->transform));
	if (fabs(ray.dir.arr[Y]) < 1e-6)
		return ;
	t = -ray.orig.arr[Y] / ray.dir.arr[Y];
	if (t < 0)
		return ;
	xs->xs[xs->count].t = t;
	xs->xs[xs->count++].shape = (t_shape *)self;
}

static t_tuple	normal_at(const t_shape *self, t_tuple p)
{
	t_tuple	normal;

	(void)p;
	normal = vector(0, 1, 0);
	normal = mat_mul_tuple(mat_t(mat_inv(self->transform)), normal);
	normal.arr[W] = 0;
	return (tuple_normalize(normal));
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
	self->base.normal_at = normal_at;
}
