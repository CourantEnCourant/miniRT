/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
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
#include "gc_libft.h"
#include "libft.h"
#include "minirt.h"
#include "tuple.h"

static bool	is_valid_color(const t_rgb *rgb)
{
	return (0.0 <= rgb->arr[R] && rgb->arr[R] <= 1.0
		&& 0.0 <= rgb->arr[G] && rgb->arr[G] <= 1.0
		&& 0.0 <= rgb->arr[B] && rgb->arr[B] <= 1.0
		&& rgb->arr[W] == 0.0);
}

bool	parse_rgb(t_rgb *rgb, char str[], t_gc *gc)
{
	t_darray	*tmp;

	tmp = gc_split(str, ',', gc);
	if (tmp->len != 3)
		return (dest_darray(tmp, gc_free), false);
	*rgb = color(ft_atoi(tmp->arr[0]) / 255.0,
			ft_atoi(tmp->arr[1]) / 255.0,
			ft_atoi(tmp->arr[2]) / 255.0);
	dest_darray(tmp, gc_free);
	return (is_valid_color(rgb));
}

bool	parse_coord(t_tuple *coord, char str[], t_gc *gc)
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

static bool	is_valid_normal(const t_tuple *normal)
{
	return (-1.0 <= normal->arr[X] && normal->arr[X] <= 1.0
		&& -1.0 <= normal->arr[Y] && normal->arr[Y] <= 1.0
		&& -1.0 <= normal->arr[Z] && normal->arr[Z] <= 1.0
		&& !deq(tuple_mod(*normal), 0));
}

bool	parse_normal(t_tuple *normal, char str[], t_gc *gc)
{
	t_darray	*tmp;

	tmp = gc_split(str, ',', gc);
	if (tmp->len != 3)
		return (dest_darray(tmp, gc_free), false);
	*normal = vector(ft_atof(tmp->arr[0]),
			ft_atof(tmp->arr[1]),
			ft_atof(tmp->arr[2]));
	dest_darray(tmp, gc_free);
	return (is_valid_normal(normal));
}
