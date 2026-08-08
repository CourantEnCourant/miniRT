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

static void	add_hit(const t_cyl *cyl, t_xs *xs, t_ray ray, double t)
{
	double	y;

	y = ray.orig.arr[Y] + t * ray.dir.arr[Y];
	if (-cyl->height / 2 < y && y < cyl->height / 2)
		add_xs(xs, &cyl->base, t);
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
	disc = sqrt(disc);
	add_hit((t_cyl *)self, xs, ray, (-b - disc) / (2 * a));
	add_hit((t_cyl *)self, xs, ray, (-b + disc) / (2 * a));
}

static t_tuple	local_normal_at(const t_shape *self, t_tuple p)
{
	(void)self;
	return (vector(p.arr[X], 0, p.arr[Z]));
}

void	init_cyl1(t_cyl *self, t_tuple coord, t_rgb rgb)
{
	init_shape(&self->base, CYL, coord, rgb);
	self->base.intersect = intersect;
	self->base.local_normal_at = local_normal_at;
}

void	init_cyl2(t_cyl *self, t_tuple normal, double radius, double height)
{
	double		phi;
	double		theta;
	t_mat		trans;
	t_tuple		coord;

	coord = self->base.coord;
	normal = tuple_normalize(normal);
	self->height = height;
	trans = mat_scal(radius, 1, radius);
	phi = acos(normal.arr[Y]);
	theta = atan2(normal.arr[X], normal.arr[Z]);
	trans = mat_mul(
			mat_mul(mat_rotate_y(theta), mat_rotate_x(phi)),
			trans);
	trans = mat_mul(
			mat_translate(coord.arr[X], coord.arr[Y], coord.arr[Z]),
			trans);
	set_matrices(&self->base, trans);
}
