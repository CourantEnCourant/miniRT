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

static void	add_hit(const t_cone *cone, t_xs *xs, t_ray ray, double t)
{
	double	y;

	y = ray.orig.arr[Y] + t * ray.dir.arr[Y];
	if (-cone->height / 2 < y && y < cone->height / 2)
		add_xs(xs, &cone->base, t);
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
	disc = sqrt(disc);
	add_hit((t_cone *)self, xs, ray, (-b - disc) / (2 * a));
	add_hit((t_cone *)self, xs, ray, (-b + disc) / (2 * a));
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

void	init_cone1(t_cone *self, t_tuple coord, t_rgb rgb)
{
	init_shape(&self->base, CONE, coord, rgb);
	self->base.intersect = intersect;
	self->base.local_normal_at = local_normal_at;
}

void	init_cone2(t_cone *self, t_tuple normal, double radius, double height)
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
