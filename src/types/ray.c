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

#include <stddef.h>
#include "minirt.h"
#include "tuple.h"

t_ray	transform(t_ray ray, const t_mat *matrix)
{
	ray.orig = mat_mul_tuple(matrix, ray.orig);
	ray.dir = mat_mul_tuple(matrix, ray.dir);
	return (ray);
}

t_tuple	ray_at(t_ray ray, double t)
{
	return (tuple_add(ray.orig, tuple_scal_mult(ray.dir, t)));
}

bool	shadow_hit(const t_conf *conf, const t_ray ray, double distance)
{
	t_xs	xs;
	size_t	i;
	t_shape	*shape;

	i = 0;
	while (i < conf->shapes->len)
	{
		shape = conf->shapes->arr[i++];
		xs.best.t = -1;
		xs.best.shape = NULL;
		shape->intersect(shape, &xs, transform(ray, &shape->transform_inv));
		if (xs.best.shape && xs.best.t < distance)
			return (true);
	}
	return (false);
}

t_ray	ray_for_pixel(const t_camera *camera, double px, double py)
{
	t_ray	ret;
	double	world_x;
	double	world_y;
	t_tuple	pixel;

	world_x = camera->half_width - (px + 0.5) * camera->pixel_size;
	world_y = camera->half_height - (py + 0.5) * camera->pixel_size;
	pixel = mat_mul_tuple(&camera->transform_inv, point(world_x, world_y, -1));
	ret.orig = mat_mul_tuple(&camera->transform_inv, point(0, 0, 0));
	ret.dir = tuple_normalize(tuple_sub(pixel, ret.orig));
	return (ret);
}

t_rgb	ray_color(t_ray r, const t_conf *conf)
{
	t_xs	xs;

	intersect_world(&xs, r, conf);
	if (!xs.best.shape)
		return (color(0, 0, 0));
	return (shade_hit(conf, prepare_computations(xs.best, r)));
}
