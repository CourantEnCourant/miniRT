/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 21:01:34 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/14 21:03:40 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stddef.h>
#include "geometry.h"
#include "minirt.h"
#include "tuple.h"

t_ray	init_ray(t_tuple point, t_tuple vec)
{
	t_ray	ret;

	ret.orig = point;
	ret.dir = vec;
	return (ret);
}

bool	ray_eq(t_ray r1, t_ray r2)
{
	if (tuple_eq(r1.orig, r2.orig) && tuple_eq(r1.dir, r2.dir))
		return (true);
	return (false);
}

t_ray	transform(t_ray ray, t_mat matrix)
{
	ray.orig = mat_mul_tuple(matrix, ray.orig);
	ray.dir = mat_mul_tuple(matrix, ray.dir);
	return (ray);
}

t_tuple	ray_at(const t_ray *ray, double t)
{
	return (tuple_add(ray->orig, tuple_scal_mult(ray->dir, t)));
}

t_xs	intersect(const t_ray *ray, const t_sphere *sphere)
{
	t_xs	ret;
	t_tuple	sp_to_ray;
	double	a;
	double	b;
	double	c;
	double	disc;

	sp_to_ray = tuple_sub(ray->orig, sphere->base.coord);
	a = tuple_dot(ray->dir, ray->dir);
	b = 2 * tuple_dot(ray->dir, sp_to_ray);
	c = tuple_dot(sp_to_ray, sp_to_ray) - sphere->radius * sphere->radius;
	disc = b * b - 4 * a * c;
	if (disc < 0)
		ret.count = 0;
	else
	{
		ret.xs[0].t = (-b - sqrt(disc)) / (2 * a);
		ret.xs[0].shape = (t_shape *)sphere;
		ret.xs[1].t = (-b + sqrt(disc)) / (2 * a);
		ret.xs[1].shape = (t_shape *)sphere;
		ret.count = 2;
	}
	return (ret);
}

t_intersection	hit(const t_xs *xs)
{
	t_intersection	none;
	unsigned int	i;

	i = 0;
	while (i < xs->count)
	{
		if (xs->xs[i].t >= 0)
			return (xs->xs[i]);
		i++;
	}
	none.t = -1;
	none.shape = NULL;
	return (none);
}
