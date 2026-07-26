/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 19:28:42 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/14 19:30:08 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"
#include "tuple.h"

static double	clamp(double v)
{
	if (v < 0.0)
		return (0.0);
	if (v > 1.0)
		return (1.0);
	return (v);
}

unsigned int	normalized_rgb_to_int(t_rgb rgb)
{
	t_rgb	clamped;

	clamped = color(clamp(rgb.arr[R]), clamp(rgb.arr[G]), clamp(rgb.arr[B]));
	return (rgb_to_int(tuple_scal_mult(clamped, 255.0)));
}

unsigned int	rgb_to_int(t_rgb rgb)
{
	return ((unsigned int)rgb.arr[R] << 16
		| (unsigned int)rgb.arr[G] << 8
		| (unsigned int)rgb.arr[B]);
}
