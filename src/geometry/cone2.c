/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone2.c                                            :+:      :+:    :+:   */
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

static bool	add_cone_help(t_cone *cone, t_darray *param)
{
	t_tuple	coord;
	t_rgb	rgb;

	if (param->len != 6)
		return (false);
	if (!parse_coord(&coord, param->arr[1], param->gc))
		return (false);
	if (!parse_rgb(&rgb, param->arr[5], param->gc))
		return (false);
	init_cone1(cone, coord, rgb);
	return (true);
}

bool	add_cone(t_darray *shapes, t_darray *param)
{
	t_cone	*cone;
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
	cone = gc_malloc(sizeof(t_cone), shapes->gc);
	if (!add_cone_help(cone, param))
		return (gc_free(cone, shapes->gc), false);
	init_cone2(cone, normal, radius, height);
	shapes->push(shapes, cone);
	return (true);
}
