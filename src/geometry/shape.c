/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 09:56:52 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/26 01:34:59 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "tuple.h"

void	init_shape(t_shape *self, enum e_type type, t_tuple coord, t_rgb rgb)
{
	self->type = type;
	self->coord = coord;
	self->transform = mat_id();
	self->material = default_material();
	self->material.rgb = rgb;
}
