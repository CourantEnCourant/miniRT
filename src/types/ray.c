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

t_tuple	ray_at(t_ray ray, double t)
{
	return (tuple_add(ray.orig, tuple_scal_mult(ray.dir, t)));
}

static void	sort_xs(t_xs *xs)
{
	t_intersection	tmp;
	int				i;
	int				j;

	i = 1;
	while (i < (int)xs->count)
	{
		tmp = xs->xs[i];
		j = i - 1;
		while (j >= 0 && xs->xs[j].t > tmp.t)
		{
			xs->xs[j + 1] = xs->xs[j];
			j--;
		}
		xs->xs[j + 1] = tmp;
		i++;
	}
}

t_xs	intersect_world(t_ray ray, const t_conf *conf)
{
	t_xs	ret;
	t_ray	local;
	t_tuple	sp_to_ray;
	double	a;
	double	b;
	double	c;
	double	disc;
	size_t	i;

	ret.count = 0;
	i = 0;
	while (i < conf->shapes->len && ret.count + 2 <= XS_SIZE)
	{
		local = transform(ray, mat_inv(((t_shape *)conf->shapes->arr[i])->transform));
		sp_to_ray = tuple_sub(local.orig, point(0, 0, 0));
		a = tuple_dot(local.dir, local.dir);
		b = 2 * tuple_dot(local.dir, sp_to_ray);
		c = tuple_dot(sp_to_ray, sp_to_ray) - 1;
		disc = b * b - 4 * a * c;
		if (disc >= 0)
		{
			ret.xs[ret.count].t = (-b - sqrt(disc)) / (2 * a);
			ret.xs[ret.count++].shape = conf->shapes->arr[i];
			ret.xs[ret.count].t = (-b + sqrt(disc)) / (2 * a);
			ret.xs[ret.count++].shape = conf->shapes->arr[i];
		}
		i++;
	}
	sort_xs(&ret);
	return (ret);
}

t_intersection	hit(const t_xs *xs)
{
	t_intersection	none;
	size_t			i;

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

t_ray	ray_for_pixel(const t_camera *camera, double px, double py)
{
	t_ray	ret;
	double	xoffset;
	double	yoffset;
	double	world_x;
	double	world_y;
	t_tuple	pixel;

	xoffset = (px + 0.5) * camera->pixel_size;
	yoffset = (py + 0.5) * camera->pixel_size;
	world_x = camera->half_width - xoffset;
	world_y = camera->half_height - yoffset;
	pixel = mat_mul_tuple(mat_inv(camera->transform), point(world_x, world_y, -1));
	ret.orig = mat_mul_tuple(mat_inv(camera->transform), point(0, 0, 0));
	ret.dir = tuple_normalize(tuple_sub(pixel, ret.orig));
	return (ret);
}
