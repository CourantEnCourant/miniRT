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

unsigned int	rgb_to_int(t_rgb rgb)
{
	t_rgb	scaled;

	scaled = tuple_scal_mult(color(clamp(rgb.arr[R]), clamp(rgb.arr[G]),
				clamp(rgb.arr[B])), 255.0);
	return ((unsigned int)scaled.arr[R] << 16
		| (unsigned int)scaled.arr[G] << 8
		| (unsigned int)scaled.arr[B]);
}
