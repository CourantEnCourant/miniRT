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
#include "vector.h"

void	init_ray(t_ray *self, t_vec3 orig, t_vec3 dir)
{
	self->orig = orig;
	self->dir = dir;
}

t_vec3	ray_at(const t_ray *ray, double t)
{
	return (vec3_add(ray->orig, vec3_scal_mult(ray->dir, t)));
}

double	hit_sphere(const t_ray *ray, const t_sphere *sphere)
{
	t_vec3	ray_to_sp;
	double	a;
	double	h;
	double	c;
	double	disc;

	ray_to_sp = vec3_sub(sphere->base.coord, ray->orig);
	a = dot_product(ray->dir, ray->dir);
	h = dot_product(ray->dir, ray_to_sp);
	c = dot_product(ray_to_sp, ray_to_sp) - sphere->radius * sphere->radius;
	disc = h * h - a * c;
	if (disc < 0)
		return (-1.0);
	return ((h - sqrt(disc)) / a);
}
