/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 19:50:05 by weizhang          #+#    #+#             */
/*   Updated: 2026/08/04 19:50:14 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "tuple.h"

static const char	*get_type(const t_shape *self)
{
	(void)self;
	return ("cone");
}

static void	add_hit(const t_cone *cone, t_xs *xs, t_ray ray, double t)
{
	double	y;

	y = ray.orig.arr[Y] + t * ray.dir.arr[Y];
	if (-cone->height / 2 < y && y < cone->height / 2)
	{
		xs->xs[xs->count].t = t;
		xs->xs[xs->count++].shape = (t_shape *)&cone->base;
	}
}

static void	intersect(const t_shape *self, t_xs *xs, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	double	disc;

	a = ray.dir.arr[X] * ray.dir.arr[X] - ray.dir.arr[Y] * ray.dir.arr[Y]
		+ ray.dir.arr[Z] * ray.dir.arr[Z];
	b = 2 * (ray.orig.arr[X] * ray.dir.arr[X]
			- ray.orig.arr[Y] * ray.dir.arr[Y]
			+ ray.orig.arr[Z] * ray.dir.arr[Z]);
	c = ray.orig.arr[X] * ray.orig.arr[X] - ray.orig.arr[Y] * ray.orig.arr[Y]
		+ ray.orig.arr[Z] * ray.orig.arr[Z];
	if (deq(a, 0))
	{
		if (!deq(b, 0))
			add_hit((t_cone *)self, xs, ray, -c / (2 * b));
		return ;
	}
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return ;
	add_hit((t_cone *)self, xs, ray, (-b - sqrt(disc)) / (2 * a));
	add_hit((t_cone *)self, xs, ray, (-b + sqrt(disc)) / (2 * a));
}

static t_tuple	local_normal_at(const t_shape *self, t_tuple p)
{
	double	y;

	(void)self;
	y = sqrt((p.arr[X] * p.arr[X] + p.arr[Z] * p.arr[Z]));
	if (p.arr[Y] > 0)
		y = -y;
	return (vector(p.arr[X], y, p.arr[Z]));
}

void	init_cone(t_cone *self, t_tuple coord, t_rgb rgb, t_tuple normal,
		double radius, double height)
{
	double	phi;
	double	theta;

	init_shape(&self->base, CONE, coord, rgb);
	normal = tuple_normalize(normal);
	self->radius = radius;
	self->height = height;
	self->base.transform = mat_scal(radius, 1, radius);
	phi = acos(normal.arr[Y]);
	theta = atan2(normal.arr[X], normal.arr[Z]);
	self->base.transform = mat_mul(
			mat_mul(mat_rotate_y(theta), mat_rotate_x(phi)),
			self->base.transform);
	self->base.transform = mat_mul(
			mat_translate(coord.arr[X], coord.arr[Y], coord.arr[Z]),
			self->base.transform);
	self->base.transform_inv = mat_inv(self->base.transform);
	self->base.get_type = get_type;
	self->base.intersect = intersect;
	self->base.local_normal_at = local_normal_at;
}
