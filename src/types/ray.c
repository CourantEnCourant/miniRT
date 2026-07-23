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

void	init_ray(t_ray *self, t_tuple orig, t_tuple dir)
{
	self->orig = orig;
	self->dir = dir;
}

t_tuple	ray_at(const t_ray *ray, double t)
{
	return (tuple_add(ray->orig, tuple_scal_mult(ray->dir, t)));
}

double	hit_sphere(const t_ray *ray, const t_sphere *sphere)
{
	t_tuple	ray_to_sp;
	double	a;
	double	h;
	double	c;
	double	disc;

	ray_to_sp = tuple_sub(sphere->base.coord, ray->orig);
	a = tuple_dot(ray->dir, ray->dir);
	h = tuple_dot(ray->dir, ray_to_sp);
	c = tuple_dot(ray_to_sp, ray_to_sp) - sphere->radius * sphere->radius;
	disc = h * h - a * c;
	if (disc < 0)
		return (-1.0);
	return ((h - sqrt(disc)) / a);
}
