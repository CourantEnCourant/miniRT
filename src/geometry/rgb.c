/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 19:28:42 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/14 19:30:08 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"
#include "tuple.h"

t_rgb	color(double r, double g, double b)
{
	return (vector(r, g, b));
}

t_rgb	color_add(t_rgb c1, t_rgb c2)
{
	return (tuple_add(c1, c2));
}

t_rgb	color_mult(t_rgb c1, t_rgb c2)
{
	return (tuple_hadamar(c1, c2));
}

t_rgb	color_sub(t_rgb c1, t_rgb c2)
{
	return (tuple_sub(c1, c2));
}

t_rgb	color_scal_mult(t_rgb c, double scale)
{
	return (tuple_scal_mult(c, scale));
}
