/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 10:12:31 by weizhang          #+#    #+#             */
/*   Updated: 2026/08/08 10:12:31 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "datastructures.h"
#include "gc.h"
#include "libft.h"
#include "minirt.h"
#include "tuple.h"

static bool	add_cyl_help(t_cyl *cyl, t_darray *param)
{
	t_tuple	coord;
	t_rgb	rgb;

	if (param->len != 6)
		return (false);
	if (!parse_coord(&coord, param->arr[1], param->gc))
		return (false);
	if (!parse_rgb(&rgb, param->arr[5], param->gc))
		return (false);
	init_cyl1(cyl, coord, rgb);
	return (true);
}

bool	add_cyl(t_darray *shapes, t_darray *param)
{
	t_cyl	*cyl;
	t_tuple	normal;
	double	radius;
	double	height;

	if (param->len != 6)
		return (false);
	if (!parse_normal(&normal, param->arr[2], param->gc))
		return (false);
	radius = ft_atof(param->arr[3]) / 2.0;
	height = ft_atof(param->arr[4]);
	if (radius <= 0 || height <= 0)
		return (false);
	cyl = gc_malloc(sizeof(t_cyl), shapes->gc);
	if (!add_cyl_help(cyl, param))
		return (gc_free(cyl, shapes->gc), false);
	init_cyl2(cyl, normal, radius, height);
	shapes->push(shapes, cyl);
	return (true);
}
