/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 10:07:35 by weizhang          #+#    #+#             */
/*   Updated: 2026/08/04 19:50:33 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "tuple.h"

static const char	*get_type(const t_shape *self)
{
	(void)self;
	return ("cylinder");
}

static void	cap_intersect(const t_cyl *cyl, t_xs *xs, t_ray ray,
				double cap_y)
{
	double	t;
	double	x;
	double	z;

	if (deq(ray.dir.arr[Y], 0))
		return ;
	t = (cap_y - ray.orig.arr[Y]) / ray.dir.arr[Y];
	x = ray.orig.arr[X] + t * ray.dir.arr[X] - cyl->base.coord.arr[X];
	z = ray.orig.arr[Z] + t * ray.dir.arr[Z] - cyl->base.coord.arr[Z];
	if (x * x + z * z <= cyl->radius * cyl->radius)
	{
		xs->xs[xs->count].t = t;
		xs->xs[xs->count++].shape = (t_shape *)cyl;
	}
}

static void	side_intersect(const t_cyl *cyl, t_xs *xs, t_ray ray)
{
	t_tuple	oc;
	double	a;
	double	b;
	double	c;
	double	disc;
	double	t0;
	double	t1;
	double	y0;
	double	y1;

	oc = tuple_sub(ray.orig, cyl->base.coord);
	a = ray.dir.arr[X] * ray.dir.arr[X] + ray.dir.arr[Z] * ray.dir.arr[Z];
	if (deq(a, 0))
		return ;
	b = 2 * (oc.arr[X] * ray.dir.arr[X] + oc.arr[Z] * ray.dir.arr[Z]);
	c = oc.arr[X] * oc.arr[X] + oc.arr[Z] * oc.arr[Z]
		- cyl->radius * cyl->radius;
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return ;
	t0 = (-b - sqrt(disc)) / (2 * a);
	t1 = (-b + sqrt(disc)) / (2 * a);
	y0 = oc.arr[Y] + t0 * ray.dir.arr[Y];
	y1 = oc.arr[Y] + t1 * ray.dir.arr[Y];
	if (y0 >= -cyl->height / 2 && y0 <= cyl->height / 2)
	{
		xs->xs[xs->count].t = t0;
		xs->xs[xs->count++].shape = (t_shape *)cyl;
	}
	if (y1 >= -cyl->height / 2 && y1 <= cyl->height / 2)
	{
		xs->xs[xs->count].t = t1;
		xs->xs[xs->count++].shape = (t_shape *)cyl;
	}
}

static void	intersect(const t_shape *self, t_xs *xs, t_ray ray)
{
	const t_cyl	*cyl;

	cyl = (const t_cyl *)self;
	side_intersect(cyl, xs, ray);
	cap_intersect(cyl, xs, ray, cyl->base.coord.arr[Y] + cyl->height / 2);
	cap_intersect(cyl, xs, ray, cyl->base.coord.arr[Y] - cyl->height / 2);
}

static t_tuple	local_normal_at(const t_shape *self, t_tuple p)
{
	const t_cyl	*cyl;

	cyl = (const t_cyl *)self;
	return (quadric_normal_at(p, -cyl->height / 2, cyl->height / 2, true, 0));
}

void	init_cyl1(t_cyl *self, t_tuple coord, t_rgb rgb, t_tuple normal)
{
	init_shape(&self->base, CYL, coord, rgb);
	self->normal = tuple_normalize(normal);
	self->base.transform = mat_translate(
			coord.arr[X], coord.arr[Y], coord.arr[Z]);
	self->base.get_type = get_type;
	self->base.intersect = intersect;
	self->base.local_normal_at = local_normal_at;
}

void	init_cyl2(t_cyl *self, double radius, double height)
{
	self->radius = radius;
	self->height = height;
}
