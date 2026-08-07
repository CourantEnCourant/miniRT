/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 11:06:09 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/21 21:26:09 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "datastructures.h"
#include "gc.h"
#include "gc_libft.h"
#include "libft.h"
#include "minirt.h"
#include "tuple.h"

bool	am_is_valid(const t_am *self);
bool	camera_is_valid(const t_camera *self);
double	degr_to_rad(double degrees);

static bool	parse_rgb(t_rgb *rgb, char str[], t_gc *gc)
{
	t_darray	*tmp;

	tmp = gc_split(str, ',', gc);
	if (tmp->len != 3)
		return (dest_darray(tmp, gc_free), false);
	*rgb = color(ft_atoi(tmp->arr[0]) / 255.0,
			ft_atoi(tmp->arr[1]) / 255.0,
			ft_atoi(tmp->arr[2]) / 255.0);
	dest_darray(tmp, gc_free);
	return (true);
}

static bool	parse_coord(t_tuple *coord, char str[], t_gc *gc)
{
	t_darray	*tmp;

	tmp = gc_split(str, ',', gc);
	if (tmp->len != 3)
		return (dest_darray(tmp, gc_free), false);
	*coord = point(ft_atof(tmp->arr[0]),
			ft_atof(tmp->arr[1]),
			ft_atof(tmp->arr[2]));
	dest_darray(tmp, gc_free);
	return (true);
}

static bool	parse_normal(t_tuple *normal, char str[], t_gc *gc)
{
	t_darray	*tmp;

	tmp = gc_split(str, ',', gc);
	if (tmp->len != 3)
		return (dest_darray(tmp, gc_free), false);
	*normal = vector(ft_atof(tmp->arr[0]),
			ft_atof(tmp->arr[1]),
			ft_atof(tmp->arr[2]));
	dest_darray(tmp, gc_free);
	return (true);
}

static bool	init_am(t_am *am, t_darray *param)
{
	if (param->len != 3)
		return (false);
	am->ratio = ft_atof(param->arr[1]);
	if (!parse_rgb(&am->rgb, param->arr[2], param->gc))
		return (false);
	return (am->is_valid(am));
}

static bool	init_camera(t_camera *cam, t_darray *param)
{
	double	half_view;
	double	aspect;
	t_tuple	up;

	if (param->len != 4)
		return (false);
	if (!parse_coord(&cam->coord, param->arr[1] ,param->gc))
		return (false);
	if (!parse_normal(&cam->normal, param->arr[2] ,param->gc))
		return (false);
	cam->normal = tuple_normalize(cam->normal);
	cam->hfov_rad = degr_to_rad(ft_atof(param->arr[3]));
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
	up = vector(0, 1, 0);
	if (fabs(cam->normal.arr[Y]) > 1 - EPSILON)
		up = vector(0, 0, 1);
	cam->transform = view_transform(cam->coord,
			tuple_add(cam->coord, cam->normal), up);
	cam->transform_inv = mat_inv(cam->transform);
	return (cam->is_valid(cam));
}

static bool	add_light(t_darray *lights, t_darray *param)
{
	t_tuple	coord;
	double	brightness;
	t_rgb	rgb;

	if (param->len != 4)
		return (false);
	if (!parse_coord(&coord, param->arr[1] ,param->gc))
		return (false);
	brightness = ft_atof(param->arr[2]);
	if (brightness < 0 || brightness > 1)
		return (false);
	if (!parse_rgb(&rgb, param->arr[3], param->gc))
		return (false);
	lights->push(lights, new_light(coord, brightness, rgb, lights->gc));
	return (true);
}

static bool	add_sphere(t_darray *shapes, t_darray *param)
{
	t_sphere	*sphere;
	t_tuple		coord;
	double		radius;
	t_rgb		rgb;

	if (param->len != 4)
		return (false);
	if (!parse_coord(&coord, param->arr[1], param->gc))
		return (false);
	radius = ft_atof(param->arr[2]) / 2.0;
	if (radius <= 0)
		return (false);
	if (!parse_rgb(&rgb, param->arr[3], param->gc))
		return (false);
	sphere = gc_malloc(sizeof(t_sphere), shapes->gc);
	init_sphere(sphere, coord, rgb, radius);
	shapes->push(shapes, sphere);
	return (true);
}

static bool	add_plane(t_darray *shapes, t_darray *param)
{
	t_plane		*plane;
	t_tuple		coord;
	t_tuple		normal;
	t_rgb		rgb;

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

static bool	add_cyl(t_darray *shapes, t_darray *param)
{
	t_cyl		*cyl;
	t_tuple		coord;
	t_tuple		normal;
	double		radius;
	double		height;
	t_rgb		rgb;

	if (param->len != 6)
		return (false);
	if (!parse_coord(&coord, param->arr[1], param->gc))
		return (false);
	if (!parse_normal(&normal, param->arr[2], param->gc))
		return (false);
	radius = ft_atof(param->arr[3]) / 2.0;
	if (radius <= 0)
		return (false);
	height = ft_atof(param->arr[4]);
	if (height <= 0)
		return (false);
	if (!parse_rgb(&rgb, param->arr[5], param->gc))
		return (false);
	cyl = gc_malloc(sizeof(t_cyl), shapes->gc);
	init_cyl(cyl, coord, rgb, normal, radius, height);
	shapes->push(shapes, cyl);
	return (true);
}

static bool	add_cone(t_darray *shapes, t_darray *param)
{
	t_cone		*cone;
	t_tuple		coord;
	t_tuple		normal;
	double		radius;
	double		height;
	t_rgb		rgb;

	if (param->len != 6)
		return (false);
	if (!parse_coord(&coord, param->arr[1], param->gc))
		return (false);
	if (!parse_normal(&normal, param->arr[2], param->gc))
		return (false);
	radius = ft_atof(param->arr[3]) / 2.0;
	if (radius <= 0)
		return (false);
	height = ft_atof(param->arr[4]);
	if (height <= 0)
		return (false);
	if (!parse_rgb(&rgb, param->arr[5], param->gc))
		return (false);
	cone = gc_malloc(sizeof(t_cone), shapes->gc);
	init_cone(cone, coord, rgb, normal, radius, height);
	shapes->push(shapes, cone);
	return (true);
}

static void	repr_conf(const t_conf *self)
{
	// This function is a temporary debug solution and will be refactored
	// later to be norminette-compliant
	size_t	i;
	t_shape	*shape;
	t_light	*light;

	if (!self->am.is_valid(&self->am))
		printf("Invalid Ambiant light\n");
	else
		printf("Ambiant light: ratio %.2f, rgb %.0f,%.0f,%.0f\n", self->am.ratio,
			self->am.rgb.arr[R], self->am.rgb.arr[G], self->am.rgb.arr[B]);
	if (!self->camera.is_valid(&self->camera))
		printf("Invalid camera\n");
	else
		printf("Camera: coord %.2f,%.2f,%.2f, normal %.2f,%.2f,%.2f, "
			"hfov_radian %.2f\n", self->camera.coord.arr[X], self->camera.coord.arr[Y],
			self->camera.coord.arr[Z], self->camera.normal.arr[X],
			self->camera.normal.arr[Y], self->camera.normal.arr[Z],
			self->camera.hfov_rad);
	printf("Loaded %zu lights:\n", self->lights->len);
	i = 0;
	while (i < self->lights->len)
	{
		light = self->lights->arr[i];
		printf("Light %zu: coord %.2f,%.2f,%.2f, brightness %.2f, rgb "
			"%.0f,%.0f,%.0f\n", i, light->coord.arr[X],
			light->coord.arr[Y], light->coord.arr[Z],
			light->brightness, light->rgb.arr[R],
			light->rgb.arr[G], light->rgb.arr[B]);
		i++;
	}
	printf("Loaded %zu shapes:\n", self->shapes->len);
	i = 0;
	while (i < self->shapes->len)
	{
		shape = self->shapes->arr[i];
		printf("Shape %zu: %s\n", i, shape->get_type(shape));
		i++;
	}
}

static void init_conf(t_conf *self, t_gc *gc)
{
	self->gc = gc;
	self->shapes = new_darray(gc);
	self->am.is_valid = am_is_valid;
	self->camera.is_valid = camera_is_valid;
	self->lights = new_darray(gc);
	self->repr = repr_conf;
}

bool	init_conf_from_file(t_conf *self, int fd, t_gc *gc)
{
	char		*line;
	t_darray	*param;
	bool		flag;

	init_conf(self, gc);
	line = gc_get_next_line(fd, gc);
	flag = true;
	while (line)
	{
		param = gc_split(line, ' ', gc);
		if (param->len == 0)
		{
			dest_darray(param, gc_free);
			gc_free(line, gc);
			line = gc_get_next_line(fd, gc);
			continue ;
		}
		if (ft_strcmp(param->arr[0], "A") == 0)
			flag = init_am(&self->am, param);
		else if (ft_strcmp(param->arr[0], "C") == 0)
			flag = init_camera(&self->camera, param);
		else if (ft_strcmp(param->arr[0], "L") == 0)
			flag = add_light(self->lights, param);
		else if (ft_strcmp(param->arr[0], "sp") == 0)
			flag = add_sphere(self->shapes, param);
		else if (ft_strcmp(param->arr[0], "pl") == 0)
			flag = add_plane(self->shapes, param);
		else if (ft_strcmp(param->arr[0], "cy") == 0)
			flag = add_cyl(self->shapes, param);
		else if (ft_strcmp(param->arr[0], "cn") == 0)
			flag = add_cone(self->shapes, param);
		else if (ft_strcmp(param->arr[0], "\n") == 0)
			;
		else
			flag = false;
		dest_darray(param, gc_free);
		if (!flag)
			break ;
		gc_free(line, gc);
		line = gc_get_next_line(fd, gc);
	}
	if (!flag)
	{
		ft_dprintf(STDERR_FILENO, "Error parsing line: %s", line);
		gc_free(line, gc);
	}
	return (flag);
}

void	dest_conf(t_conf *self)
{
	dest_darray(self->lights, gc_free);
	dest_darray(self->shapes, gc_free);
}

t_mat	view_transform(t_tuple from, t_tuple to, t_tuple up)
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
