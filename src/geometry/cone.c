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

static void	cap_intersect(const t_cone *cone, t_xs *xs, t_ray ray)
{
	double	cap_y;
	double	t;
	double	x;
	double	z;

	if (deq(ray.dir.arr[Y], 0))
		return ;
	cap_y = cone->base.coord.arr[Y] + cone->height;
	t = (cap_y - ray.orig.arr[Y]) / ray.dir.arr[Y];
	x = ray.orig.arr[X] + t * ray.dir.arr[X] - cone->base.coord.arr[X];
	z = ray.orig.arr[Z] + t * ray.dir.arr[Z] - cone->base.coord.arr[Z];
	if (x * x + z * z <= cone->radius * cone->radius)
	{
		xs->xs[xs->count].t = t;
		xs->xs[xs->count++].shape = (t_shape *)cone;
	}
}

static void	add_if_in_range(const t_cone *cone, t_xs *xs, t_tuple oc,
		t_ray ray, double t)
{
	double  y;

	y = oc.arr[Y] + t * ray.dir.arr[Y];
	if (y >= 0 && y <= cone->height)
	{
		xs->xs[xs->count].t = t;
		xs->xs[xs->count++].shape = (t_shape *)cone;
	}
}

static void	side_intersect(const t_cone *cone, t_xs *xs, t_ray ray)
{
	t_tuple	oc;
	double	k;
	double	a;
	double	b;
	double	c;
	double	disc;

	oc = tuple_sub(ray.orig, cone->base.coord);
	k = cone->radius / cone->height;
	a = ray.dir.arr[X] * ray.dir.arr[X] + ray.dir.arr[Z] * ray.dir.arr[Z]
		- k * k * ray.dir.arr[Y] * ray.dir.arr[Y];
	b = 2 * (oc.arr[X] * ray.dir.arr[X] + oc.arr[Z] * ray.dir.arr[Z]
		- k * k * oc.arr[Y] * ray.dir.arr[Y]);
	c = oc.arr[X] * oc.arr[X] + oc.arr[Z] * oc.arr[Z]
		- k * k * oc.arr[Y] * oc.arr[Y];
	if (deq(a, 0))
	{
		if (!deq(b, 0))
			add_if_in_range(cone, xs, oc, ray, -c / b);
		return ;
	}
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return ;
	add_if_in_range(cone, xs, oc, ray, (-b - sqrt(disc)) / (2 * a));
	add_if_in_range(cone, xs, oc, ray, (-b + sqrt(disc)) / (2 * a));
}

static void	intersect(const t_shape *self, t_xs *xs, t_ray ray)
{
	const t_cone	*cone;

	cone = (const t_cone *)self;
	side_intersect(cone, xs, ray);
	cap_intersect(cone, xs, ray);
}

static t_tuple	local_normal_at(const t_shape *self, t_tuple p)
{
	const t_cone	*cone;
	double			k2;

	cone = (const t_cone *)self;
	k2 = (cone->radius / cone->height) * (cone->radius / cone->height);
	return (quadric_normal_at(p, 0, cone->height, false,
			2 * k2 * p.arr[Y]));
}

void	init_cone(t_cone *self, t_tuple coord, t_rgb rgb, double radius,
		double height)
{
	init_shape(&self->base, CONE, coord, rgb);
	self->radius = radius;
	self->height = height;
	self->base.transform = mat_translate(
			coord.arr[X], coord.arr[Y], coord.arr[Z]);
	self->base.get_type = get_type;
	self->base.intersect = intersect;
	self->base.local_normal_at = local_normal_at;
}
