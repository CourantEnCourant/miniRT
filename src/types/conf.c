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

static bool	init_am(t_conf *self, t_darray *param)
{
	t_darray	*rgb;

	if (param->len != 3)
		return (false);
	self->am.ratio = atof(param->arr[1]);
	rgb = gc_split(param->arr[2], ',', self->gc);
	if (rgb->len != 3)
		return (dest_darray(rgb, gc_free), false);
	self->am.rgb = (t_rgb){ft_atoi(rgb->arr[0]), ft_atoi(rgb->arr[1]),
		ft_atoi(rgb->arr[2])};
	self->valid_am = true;
	return (dest_darray(rgb, gc_free), true);
}

static bool	init_camera(t_conf *self, t_darray *param)
{
	t_darray	*tmp;

	if (param->len != 4)
		return (false);
	self->camera.fov = atof(param->arr[3]);
	tmp = gc_split(param->arr[1], ',', self->gc);
	if (tmp->len != 3)
		return (dest_darray(tmp, gc_free), false);
	self->camera.coord = (t_vec3){{atof(tmp->arr[0]), atof(tmp->arr[1]),
		atof(tmp->arr[2])}};
	dest_darray(tmp, gc_free);
	tmp = gc_split(param->arr[2], ',', self->gc);
	if (tmp->len != 3)
		return (dest_darray(tmp, gc_free), false);
	self->camera.normal = (t_vec3){{atof(tmp->arr[0]), atof(tmp->arr[1]),
		atof(tmp->arr[2])}};
	self->valid_camera = true;
	return (dest_darray(tmp, gc_free), true);
}

static bool	init_light(t_conf *self, t_darray *param)
{
	t_darray	*tmp;

	if (param->len != 4)
		return (false);
	self->light.brightness = atof(param->arr[2]);
	tmp = gc_split(param->arr[1], ',', self->gc);
	if (tmp->len != 3)
		return (dest_darray(tmp, gc_free), false);
	self->light.coord = (t_vec3){{atof(tmp->arr[0]), atof(tmp->arr[1]),
		atof(tmp->arr[2])}};
	dest_darray(tmp, gc_free);
	tmp = gc_split(param->arr[3], ',', self->gc);
	if (tmp->len != 3)
		return (dest_darray(tmp, gc_free), false);
	self->light.rgb = (t_rgb){ft_atoi(tmp->arr[0]), ft_atoi(tmp->arr[1]),
		ft_atoi(tmp->arr[2])};
	self->valid_light = true;
	return (dest_darray(tmp, gc_free), true);
}

static bool	add_sphere(t_conf *self, t_darray *param)
{
	t_sphere	*sphere;
	t_vec3		coord;
	t_rgb		rgb;
	double		radius;
	t_darray	*tmp;

	if (param->len != 4)
		return (false);
	radius = atof(param->arr[2]) / 2.0;
	if (radius <= 0)
		return (false);
	tmp = gc_split(param->arr[1], ',', self->gc);
	if (tmp->len != 3)
		return (dest_darray(tmp, gc_free), false);
	rgb = (t_rgb){ft_atoi(tmp->arr[0]), ft_atoi(tmp->arr[1]),
		ft_atoi(tmp->arr[2])};
	dest_darray(tmp, gc_free);
	tmp = gc_split(param->arr[3], ',', self->gc);
	if (tmp->len != 3)
		return (dest_darray(tmp, gc_free), false);
	coord = (t_vec3){{atof(tmp->arr[0]), atof(tmp->arr[1]), atof(tmp->arr[2])}};
	dest_darray(tmp, gc_free);
	sphere = gc_malloc(sizeof(t_sphere), self->gc);
	init_sphere(sphere, coord, rgb, radius);
	self->shapes->push(self->shapes, sphere);
	return (true);
}

static bool	add_plane(t_conf *self, t_darray *param)
{
	(void)self;
	(void)param;
	return (true);
}

static bool	add_cyl(t_conf *self, t_darray *param)
{
	(void)self;
	(void)param;
	return (true);
}

static const char	*shape_name(enum e_type type)
{
	if (type == SPHERE)
		return ("sphere");
	if (type == PLANE)
		return ("plane");
	return ("cylinder");
}

static void	repr_conf(const t_conf *self)
{
	// This function is a temporary debug solution and will be refactored
	// later to be norminette-compliant
	size_t	i;

	if (!self->valid_am)
		printf("Invalid Ambiant light\n");
	else
		printf("Ambiant light: ratio %.2f, rgb %u,%u,%u\n", self->am.ratio,
			self->am.rgb.r, self->am.rgb.g, self->am.rgb.b);
	if (!self->valid_camera)
		printf("Invalid camera\n");
	else
		printf("Camera: coord %.2f,%.2f,%.2f, normal %.2f,%.2f,%.2f, "
			"fov %.2f\n", self->camera.coord.arr[X], self->camera.coord.arr[Y],
			self->camera.coord.arr[Z], self->camera.normal.arr[X],
			self->camera.normal.arr[Y], self->camera.normal.arr[Z],
			self->camera.fov);
	if (!self->valid_light)
		printf("Invalid light\n");
	else
		printf("Light: coord %.2f,%.2f,%.2f, brightness %.2f, rgb "
			"%u,%u,%u\n", self->light.coord.arr[X], self->light.coord.arr[Y],
			self->light.coord.arr[Z], self->light.brightness,
			self->light.rgb.r, self->light.rgb.g, self->light.rgb.b);
	printf("Loaded %zu shapes:\n", self->shapes->len);
	i = 0;
	while (i < self->shapes->len)
		printf("  %s\n",
			shape_name(((t_shape *)self->shapes->arr[i++])->type));
}

static void init_conf(t_conf *self, t_gc *gc)
{
	self->gc = gc;
	self->shapes = new_darray(gc);
	self->valid_am = false;
	self->valid_camera = false;
	self->valid_light = false;
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
		if (ft_strcmp(param->arr[0], "A") == 0)
			flag = init_am(self, param);
		else if (ft_strcmp(param->arr[0], "C") == 0)
			flag = init_camera(self, param);
		else if (ft_strcmp(param->arr[0], "L") == 0)
			flag = init_light(self, param);
		else if (ft_strcmp(param->arr[0], "sp") == 0)
			flag = add_sphere(self, param);
		else if (ft_strcmp(param->arr[0], "pl") == 0)
			flag = add_plane(self, param);
		else if (ft_strcmp(param->arr[0], "cy") == 0)
			flag = add_cyl(self, param);
		else if (!line[0])
			;
		else
			flag = false;
		dest_darray(param, gc_free);
		if (!flag)
		{
			ft_dprintf(STDERR_FILENO, "Error parsing line: %s", line);
			gc_free(line, gc);
			break ;
		}
		gc_free(line, gc);
		line = gc_get_next_line(fd, gc);
	}
	return (flag);
}

void	dest_conf(t_conf *self)
{
	dest_darray(self->shapes, gc_free);
}
