/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 11:06:09 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/09 11:20:48 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "datastructures.h"
#include "gc.h"
#include "gc_libft.h"
#include "geometry.h"
#include "libft.h"
#include "minirt.h"
#include "vector.h"

bool	am_is_valid(const t_am *self);
bool	camera_is_valid(const t_camera *self);
bool	light_is_valid(const t_light *self);

static bool	parse_rgb(t_rgb *rgb, char str[], t_gc *gc)
{
	t_darray	*tmp;

	tmp = gc_split(str, ',', gc);
	if (tmp->len != 3)
		return (dest_darray(tmp, gc_free), false);
	rgb->r = ft_atoi(tmp->arr[0]);
	rgb->g = ft_atoi(tmp->arr[1]);
	rgb->b = ft_atoi(tmp->arr[2]);
	dest_darray(tmp, gc_free);
	return (true);
}

static bool	parse_coord(t_vec3 *coord, char str[], t_gc *gc)
{
	t_darray	*tmp;

	tmp = gc_split(str, ',', gc);
	if (tmp->len != 3)
		return (dest_darray(tmp, gc_free), false);
	coord->arr[X] = atof(tmp->arr[0]);
	coord->arr[Y] = atof(tmp->arr[1]);
	coord->arr[Z] = atof(tmp->arr[2]);
	dest_darray(tmp, gc_free);
	return (true);
}

static bool	parse_normal(t_vec3 *normal, char str[], t_gc *gc)
{
	return (parse_coord(normal, str, gc));
}

static bool	init_am(t_am *am, t_darray *param)
{
	if (param->len != 3)
		return (false);
	am->ratio = atof(param->arr[1]);
	if (!parse_rgb(&am->rgb, param->arr[2], param->gc))
		return (false);
	return (am->is_valid(am));
}

static bool	init_camera(t_camera *cam, t_darray *param)
{
	if (param->len != 4)
		return (false);
	if (!parse_coord(&cam->coord, param->arr[1] ,param->gc))
		return (false);
	if (!parse_normal(&cam->normal, param->arr[2] ,param->gc))
		return (false);
	cam->fov = atof(param->arr[3]);
	return (cam->is_valid(cam));
}

static bool	init_light(t_light *light, t_darray *param)
{
	if (param->len != 4)
		return (false);
	if (!parse_coord(&light->coord, param->arr[1] ,param->gc))
		return (false);
	light->brightness = atof(param->arr[2]);
	if (!parse_rgb(&light->rgb, param->arr[3], param->gc))
		return (false);
	return (light->is_valid(light));
}

static bool	add_sphere(t_darray *shapes, t_darray *param)
{
	t_sphere	*sphere;
	t_vec3		coord;
	double		radius;
	t_rgb		rgb;

	if (param->len != 4)
		return (false);
	if (!parse_coord(&coord, param->arr[1], param->gc))
		return (false);
	radius = atof(param->arr[2]) / 2.0;
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
	t_vec3		coord;
	t_vec3		normal;
	t_rgb		rgb;

	if (param->len != 4)
		return (false);
	if (!parse_coord(&coord, param->arr[1], param->gc))
		return (false);
	if (!parse_coord(&normal, param->arr[2], param->gc))
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
	t_vec3		coord;
	t_vec3		normal;
	double		radius;
	double		height;
	t_rgb		rgb;

	if (param->len != 6)
		return (false);
	if (!parse_coord(&coord, param->arr[1], param->gc))
		return (false);
	if (!parse_coord(&normal, param->arr[2], param->gc))
		return (false);
	radius = atof(param->arr[3]) / 2.0;
	if (radius <= 0)
		return (false);
	height = atof(param->arr[4]);
	if (height <= 0)
		return (false);
	if (!parse_rgb(&rgb, param->arr[5], param->gc))
		return (false);
	cyl = gc_malloc(sizeof(t_cyl), shapes->gc);
	init_cyl1(cyl, coord, rgb, normal);
	init_cyl2(cyl, radius, height);
	shapes->push(shapes, cyl);
	return (true);
}

static void	repr_conf(const t_conf *self)
{
	// This function is a temporary debug solution and will be refactored
	// later to be norminette-compliant
	size_t	i;
	t_shape	*shape;

	if (!self->am.is_valid(&self->am))
		printf("Invalid Ambiant light\n");
	else
		printf("Ambiant light: ratio %.2f, rgb %u,%u,%u\n", self->am.ratio,
			self->am.rgb.r, self->am.rgb.g, self->am.rgb.b);
	if (!self->camera.is_valid(&self->camera))
		printf("Invalid camera\n");
	else
		printf("Camera: coord %.2f,%.2f,%.2f, normal %.2f,%.2f,%.2f, "
			"fov %.2f\n", self->camera.coord.arr[X], self->camera.coord.arr[Y],
			self->camera.coord.arr[Z], self->camera.normal.arr[X],
			self->camera.normal.arr[Y], self->camera.normal.arr[Z],
			self->camera.fov);
	if (!self->light.is_valid(&self->light))
		printf("Invalid light\n");
	else
		printf("Light: coord %.2f,%.2f,%.2f, brightness %.2f, rgb "
			"%u,%u,%u\n", self->light.coord.arr[X], self->light.coord.arr[Y],
			self->light.coord.arr[Z], self->light.brightness,
			self->light.rgb.r, self->light.rgb.g, self->light.rgb.b);
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
	self->light.is_valid = light_is_valid;
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
			flag = init_light(&self->light, param);
		else if (ft_strcmp(param->arr[0], "sp") == 0)
			flag = add_sphere(self->shapes, param);
		else if (ft_strcmp(param->arr[0], "pl") == 0)
			flag = add_plane(self->shapes, param);
		else if (ft_strcmp(param->arr[0], "cy") == 0)
			flag = add_cyl(self->shapes, param);
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
	dest_darray(self->shapes, gc_free);
}
