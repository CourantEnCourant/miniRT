/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyperboloid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 19:50:38 by weizhang          #+#    #+#             */
/*   Updated: 2026/08/04 19:50:41 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "tuple.h"

static const char	*get_type(const t_shape *self)
{
	(void)self;
	return ("hyperboloid");
}

static void	cap_intersect(const t_hyper *hyp, t_xs *xs, t_ray ray,
		double cap_y)
{
	double	t;
	double	x;
	double	z;
	double	local_y;

	if (deq(ray.dir.arr[Y], 0))
		return ;
	t = (cap_y - ray.orig.arr[Y]) / ray.dir.arr[Y];
	x = ray.orig.arr[X] + t * ray.dir.arr[X] - hyp->base.coord.arr[X];
	z = ray.orig.arr[Z] + t * ray.dir.arr[Z] - hyp->base.coord.arr[Z];
	local_y = cap_y - hyp->base.coord.arr[Y];
	if (x * x + z * z <= hyp->w * hyp->w + hyp->a * local_y * local_y)
	{
		xs->xs[xs->count].t = t;
		xs->xs[xs->count++].shape = (t_shape *)hyp;
	}
}

static void	add_if_in_range(const t_hyper *hyp, t_xs *xs, t_tuple oc,
		t_ray ray, double t)
{
	double	y;

	y = oc.arr[Y] + t * ray.dir.arr[Y];
	if (y >= -hyp->height / 2 && y <= hyp->height / 2)
	{
		xs->xs[xs->count].t = t;
		xs->xs[xs->count++].shape = (t_shape *)hyp;
	}
}

static void	side_intersect(const t_hyper *hyp, t_xs *xs, t_ray ray)
{
	t_tuple	oc;
	double	a;
	double	b;
	double	c;
	double	disc;

	oc = tuple_sub(ray.orig, hyp->base.coord);
	a = ray.dir.arr[X] * ray.dir.arr[X] + ray.dir.arr[Z] * ray.dir.arr[Z]
		- hyp->a * ray.dir.arr[Y] * ray.dir.arr[Y];
	b = 2 * (oc.arr[X] * ray.dir.arr[X] + oc.arr[Z] * ray.dir.arr[Z]
		- hyp->a * oc.arr[Y] * ray.dir.arr[Y]);
	c = oc.arr[X] * oc.arr[X] + oc.arr[Z] * oc.arr[Z]
		- hyp->a * oc.arr[Y] * oc.arr[Y] - hyp->w * hyp->w;
	if (deq(a, 0))
	{
		if (!deq(b, 0))
			add_if_in_range(hyp, xs, oc, ray, -c / b);
		return ;
	}
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return ;
	add_if_in_range(hyp, xs, oc, ray, (-b - sqrt(disc)) / (2 * a));
	add_if_in_range(hyp, xs, oc, ray, (-b + sqrt(disc)) / (2 * a));
}

static void	intersect(const t_shape *self, t_xs *xs, t_ray ray)
{
	const t_hyper	*hyp;

	hyp = (const t_hyper *)self;
	side_intersect(hyp, xs, ray);
	cap_intersect(hyp, xs, ray, hyp->base.coord.arr[Y] + hyp->height / 2);
	cap_intersect(hyp, xs, ray, hyp->base.coord.arr[Y] - hyp->height / 2);
}

static t_tuple	local_normal_at(const t_shape *self, t_tuple p)
{
	const t_hyper	*hyp;

	hyp = (const t_hyper *)self;
	return (quadric_normal_at(p, -hyp->height / 2, hyp->height / 2,
			true, 2 * hyp->a * p.arr[Y]));
}

void	init_hyper(t_hyper *self, t_tuple coord, t_rgb rgb, double w,
		double a, double height)
{
	init_shape(&self->base, HYPERBOLOID, coord, rgb);
	self->w = w;
	self->a = a;
	self->height = height;
	self->base.transform = mat_translate(
			coord.arr[X], coord.arr[Y], coord.arr[Z]);
	self->base.get_type = get_type;
	self->base.intersect = intersect;
	self->base.local_normal_at = local_normal_at;
}
