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
#include "geometry.h"
#include "minirt.h"
#include "tuple.h"

void	init_ray(t_ray *self, t_tuple point, t_tuple vec)
{
	self->orig = point;
	self->dir = vec;
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
		ret.xs[0] = (-b - sqrt(disc)) / (2 * a);
		ret.xs[1] = (-b + sqrt(disc)) / (2 * a);
		ret.count = 2;
	}
	return (ret);
}
