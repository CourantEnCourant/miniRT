/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 19:52:31 by weizhang          #+#    #+#             */
/*   Updated: 2026/08/04 19:53:40 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "tuple.h"

static const char	*get_type(const t_shape *self)
{
	(void)self;
	return ("paraboloid");
}

static void	cap_intersect(const t_para *para, t_xs *xs, t_ray ray)
{
	double	cap_y;
	double	t;
	double	x;
	double	z;

	if (deq(ray.dir.arr[Y], 0))
		return ;
	cap_y = para->base.coord.arr[Y] + para->height;
	t = (cap_y - ray.orig.arr[Y]) / ray.dir.arr[Y];
	x = ray.orig.arr[X] + t * ray.dir.arr[X] - para->base.coord.arr[X];
	z = ray.orig.arr[Z] + t * ray.dir.arr[Z] - para->base.coord.arr[Z];
	if (x * x + z * z <= para->radius * para->radius)
	{
	xs->xs[xs->count].t = t;
	xs->xs[xs->count++].shape = (t_shape *)para;
	}
}

static void	add_if_in_range(const t_para *para, t_xs *xs, t_tuple oc,
	t_ray ray, double t)
{
	double	y;

	y = oc.arr[Y] + t * ray.dir.arr[Y];
	if (y >= 0 && y <= para->height)
	{
	xs->xs[xs->count].t = t;
	xs->xs[xs->count++].shape = (t_shape *)para;
	}
}

static void	side_intersect(const t_para *para, t_xs *xs, t_ray ray)
{
	t_tuple	oc;
	double	k;
	double	a;
	double	b;
	double	c;
	double	disc;

	oc = tuple_sub(ray.orig, para->base.coord);
	k = para->radius * para->radius / para->height;
	a = ray.dir.arr[X] * ray.dir.arr[X] + ray.dir.arr[Z] * ray.dir.arr[Z];
	b = 2 * (oc.arr[X] * ray.dir.arr[X] + oc.arr[Z] * ray.dir.arr[Z])
	- k * ray.dir.arr[Y];
	c = oc.arr[X] * oc.arr[X] + oc.arr[Z] * oc.arr[Z]
	- k * oc.arr[Y];
	if (deq(a, 0) && !deq(b, 0))
	{
		add_if_in_range(para, xs, oc, ray, -c / b);
		return ;
	}
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return ;
	add_if_in_range(para, xs, oc, ray, (-b - sqrt(disc)) / (2 * a));
	add_if_in_range(para, xs, oc, ray, (-b + sqrt(disc)) / (2 * a));
}

static void	intersect(const t_shape *self, t_xs *xs, t_ray ray)
{
	const t_para	*para;

	para = (const t_para *)self;
	side_intersect(para, xs, ray);
	cap_intersect(para, xs, ray);
}

static t_tuple	local_normal_at(const t_shape *self, t_tuple p)
{
	const t_para	*para;

	para = (const t_para *)self;
	return (quadric_normal_at(p, 0, para->height, false,
			para->radius * para->radius / para->height));
}

void	init_para(t_para *self, t_tuple coord, t_rgb rgb, double radius,
	double height)
{
	init_shape(&self->base, PARABOLOID, coord, rgb);
	self->radius = radius;
	self->height = height;
	self->base.transform = mat_translate(
			coord.arr[X], coord.arr[Y], coord.arr[Z]);
	self->base.get_type = get_type;
	self->base.intersect = intersect;
	self->base.local_normal_at = local_normal_at;
}
