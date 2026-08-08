/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 10:07:35 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/09 10:09:45 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include "datastructures.h"
#include "gc.h"
#include "libft.h"
#include "minirt.h"
#include "tuple.h"

static void	intersect(const t_shape *self, t_xs *xs, t_ray ray)
{
	double	t;

	if (deq(ray.dir.arr[Y], 0))
		return ;
	t = -ray.orig.arr[Y] / ray.dir.arr[Y];
	add_xs(xs, self, t);
}

static t_tuple	local_normal_at(const t_shape *self, t_tuple p)
{
	(void)self;
	(void)p;
	return (vector(0, 1, 0));
}

static void	init_plane(t_plane *self, t_tuple coord, t_rgb rgb, t_tuple normal)
{
	double	phi;
	double	theta;
	t_mat	rot;
	t_mat	trans;

	init_shape(&self->base, PLANE, coord, rgb);
	normal = tuple_normalize(normal);
	phi = acos(normal.arr[Y]);
	theta = atan2(normal.arr[X], normal.arr[Z]);
	rot = mat_mul(mat_rotate_y(theta), mat_rotate_x(phi));
	trans = mat_translate(
			coord.arr[X],
			coord.arr[Y],
			coord.arr[Z]);
	trans = mat_mul(trans, rot);
	set_matrices(&self->base, trans);
	self->base.intersect = intersect;
	self->base.local_normal_at = local_normal_at;
}

bool	add_plane(t_darray *shapes, t_darray *param)
{
	t_plane	*plane;
	t_tuple	coord;
	t_tuple	normal;
	t_rgb	rgb;

	if (param->len != 4)
		return (false);
	if (!parse_coord(&coord, param->arr[1], param->gc))
		return (false);
	if (!parse_normal(&normal, param->arr[2], param->gc))
		return (false);
	if (!parse_rgb(&rgb, param->arr[3], param->gc))
		return (false);
	plane = gc_malloc(sizeof(t_plane), shapes->gc);
	init_plane(plane, coord, rgb, normal);
	shapes->push(shapes, plane);
	return (true);
}
