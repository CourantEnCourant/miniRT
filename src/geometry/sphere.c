/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 10:07:35 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/09 10:08:41 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "tuple.h"

static const char	*get_type(const t_shape *self)
{
	(void)self;
	return ("sphere");
}

static void	intersect(const t_shape *self, t_xs *xs, t_ray ray)
{
	t_tuple	sp_to_ray;
	double	a;
	double	b;
	double	c;
	double	disc;

	ray = transform(ray, mat_inv(self->transform));
	sp_to_ray = tuple_sub(ray.orig, point(0, 0, 0));
	a = tuple_dot(ray.dir, ray.dir);
	b = 2 * tuple_dot(ray.dir, sp_to_ray);
	c = tuple_dot(sp_to_ray, sp_to_ray) - 1;
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return ;
	xs->xs[xs->count].t = (-b - sqrt(disc)) / (2 * a);
	xs->xs[xs->count++].shape = (t_shape *)self;
	xs->xs[xs->count].t = (-b + sqrt(disc)) / (2 * a);
	xs->xs[xs->count++].shape = (t_shape *)self;
}

void	init_sphere(t_sphere *self, t_tuple coord, t_rgb rgb, double radius)
{
	init_shape(&self->base, SPHERE, coord, rgb);
	self->radius = radius;
	self->base.transform = mat_mul(mat_translate(coord.arr[X], coord.arr[Y], coord.arr[Z]), mat_scal(radius, radius, radius));
	self->base.get_type = get_type;
	self->base.intersect = intersect;
}

t_tuple	normal_at(const t_sphere *sp, t_tuple p)
{
	t_tuple	normal;

	p = mat_mul_tuple(mat_inv(sp->base.transform), p);
	normal = tuple_sub(p, point(0, 0, 0));
	normal = mat_mul_tuple(mat_t(mat_inv(sp->base.transform)), normal);
	normal.arr[W] = 0;
	return (tuple_normalize(normal));
}

t_tuple	reflect(t_tuple in, t_tuple normal)
{
	return (tuple_sub(in, tuple_scal_mult(normal, 2 * tuple_dot(in, normal))));
}
