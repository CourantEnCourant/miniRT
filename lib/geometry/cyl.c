/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 10:07:35 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/09 10:11:58 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"
#include "tuple.h"

void	init_cyl1(t_cyl *self, t_tuple coord, t_rgb rgb, t_tuple normal)
{
	init_shape(&self->base, CYL, coord, rgb);
	self->normal = normal;
}

void	init_cyl2(t_cyl *self, double radius, double height)
{
	self->radius = radius;
	self->height = height;
}
