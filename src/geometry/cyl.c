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

static void	add_hit(const t_cyl *cyl, t_xs *xs, t_ray ray, double t)
{
	double	y;

	y = ray.orig.arr[Y] + t * ray.dir.arr[Y];
	if (-cyl->height / 2 < y && y < cyl->height / 2)
	{
		xs->xs[xs->count].t = t;
		xs->xs[xs->count++].shape = (t_shape *)&cyl->base;
	}
}

static void	intersect(const t_shape *self, t_xs *xs, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	double	disc;

	a = ray.dir.arr[X] * ray.dir.arr[X] + ray.dir.arr[Z] * ray.dir.arr[Z];
	if (deq(a, 0))
		return ;
	b = 2 * ray.orig.arr[X] * ray.dir.arr[X]
		+ 2 * ray.orig.arr[Z] * ray.dir.arr[Z];
	c = ray.orig.arr[X] * ray.orig.arr[X]
		+ ray.orig.arr[Z] * ray.orig.arr[Z] - 1;
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return ;
	add_hit((t_cyl *)self, xs, ray, (-b - sqrt(disc)) / (2 * a));
	add_hit((t_cyl *)self, xs, ray, (-b + sqrt(disc)) / (2 * a));
}

static t_tuple	local_normal_at(const t_shape *self, t_tuple p)
{
	(void)self;
	return (vector(p.arr[X], 0, p.arr[Z]));
}

void	init_cyl(t_cyl *self, t_tuple coord, t_rgb rgb, t_tuple normal, double radius, double height)
{
	double	phi;
	double	theta;
	t_mat	trans;

	init_shape(&self->base, CYL, coord, rgb);
	self->normal = tuple_normalize(normal);
	self->radius = radius;
	self->height = height;
	trans = mat_scal(radius, 1, radius);
	phi = acos(self->normal.arr[Y]);
	theta = atan2(self->normal.arr[X], self->normal.arr[Z]);
	trans = mat_mul(
			mat_mul(mat_rotate_y(theta), mat_rotate_x(phi)),
			trans);
	trans = mat_mul(
			mat_translate(coord.arr[X], coord.arr[Y], coord.arr[Z]),
			trans);
	set_matrices(&self->base, trans);
	self->base.get_type = get_type;
	self->base.intersect = intersect;
	self->base.local_normal_at = local_normal_at;
}
