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

static void	init_conf(t_conf *self, t_gc *gc)
{
	self->gc = gc;
	self->shapes = new_darray(gc);
	self->lights = new_darray(gc);
}

static bool	parse_line(t_conf *self, t_darray *param)
{
	if (param->len == 0)
		return (true);
	if (ft_strcmp(param->arr[0], "A") == 0)
		return (init_am(&self->am, param));
	else if (ft_strcmp(param->arr[0], "C") == 0)
		return (init_camera(&self->camera, param));
	else if (ft_strcmp(param->arr[0], "L") == 0)
		return (add_light(self->lights, param));
	else if (ft_strcmp(param->arr[0], "sp") == 0)
		return (add_sphere(self->shapes, param));
	else if (ft_strcmp(param->arr[0], "pl") == 0)
		return (add_plane(self->shapes, param));
	else if (ft_strcmp(param->arr[0], "cy") == 0)
		return (add_cyl(self->shapes, param));
	else if (ft_strcmp(param->arr[0], "cn") == 0)
		return (add_cone(self->shapes, param));
	else if (ft_strcmp(param->arr[0], "\n") == 0)
		return (true);
	else
		return (false);
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
		flag = parse_line(self, param);
		dest_darray(param, gc_free);
		gc_free(line, gc);
		if (!flag)
			break ;
		line = gc_get_next_line(fd, gc);
	}
	return (flag);
}

void	dest_conf(t_conf *self)
{
	dest_darray(self->lights, gc_free);
	dest_darray(self->shapes, gc_free);
}
