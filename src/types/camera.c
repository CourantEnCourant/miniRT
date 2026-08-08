/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 23:14:10 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/21 21:28:03 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include "datastructures.h"
#include "libft.h"
#include "minirt.h"
#include "tuple.h"

double	degr_to_rad(double degrees);

static bool	is_valid(const t_camera *self)
{
	return (-1.0 <= self->normal.arr[X] && self->normal.arr[X] <= 1.0
		&& -1.0 <= self->normal.arr[Y] && self->normal.arr[Y] <= 1.0
		&& -1.0 <= self->normal.arr[Z] && self->normal.arr[Z] <= 1.0
		&& 0.0 <= self->hfov_rad && self->hfov_rad <= M_PI);
}

static void	init_camera_view(t_camera *cam)
{
	double	half_view;
	double	aspect;

	half_view = tan(cam->hfov_rad / 2);
	aspect = (double)WIN_W / WIN_H;
	if (aspect >= 1)
	{
		cam->half_width = half_view;
		cam->half_height = half_view / aspect;
	}
	else
	{
		cam->half_width = half_view * aspect;
		cam->half_height = half_view;
	}
	cam->pixel_size = cam->half_width * 2 / WIN_W;
}

static t_mat	view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple	forward;
	t_tuple	upn;
	t_tuple	left;
	t_tuple	true_up;
	t_mat	orientation;

	forward = tuple_normalize(tuple_sub(to, from));
	upn = tuple_normalize(up);
	left = cross_product(forward, upn);
	true_up = cross_product(left, forward);
	orientation = (t_mat){{{left.arr[X], left.arr[Y], left.arr[Z], 0},
	{true_up.arr[X], true_up.arr[Y], true_up.arr[Z], 0},
	{-forward.arr[X], -forward.arr[Y], -forward.arr[Z], 0},
	{0, 0, 0, 1}}, 4};
	return (mat_mul(orientation,
			mat_translate(-from.arr[X], -from.arr[Y], -from.arr[Z])));
}

bool	init_camera(t_camera *cam, t_darray *param)
{
	t_tuple	up;

	if (param->len != 4)
		return (false);
	if (!parse_coord(&cam->coord, param->arr[1], param->gc))
		return (false);
	if (!parse_normal(&cam->normal, param->arr[2], param->gc))
		return (false);
	cam->normal = tuple_normalize(cam->normal);
	cam->hfov_rad = degr_to_rad(ft_atof(param->arr[3]));
	init_camera_view(cam);
	up = vector(0, 1, 0);
	if (fabs(cam->normal.arr[Y]) > 1 - EPSILON)
		up = vector(0, 0, 1);
	cam->transform = view_transform(cam->coord,
			tuple_add(cam->coord, cam->normal), up);
	cam->transform_inv = mat_inv(cam->transform);
	return (is_valid(cam));
}
