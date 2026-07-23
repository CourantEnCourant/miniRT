/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 09:56:52 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/09 09:59:26 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"
#include "tuple.h"

static const char	*get_type(const t_shape *self)
{
	if (self->type == SPHERE)
		return ("sphere");
	if (self->type == PLANE)
		return ("plane");
	if (self->type == CYL)
		return ("cylinder");
	else
		return ("unrecognized");
}

void	init_shape(t_shape *self, enum e_type type, t_tuple coord, t_rgb rgb)
{
	self->type = type;
	self->coord = coord;
	self->rgb = rgb;
	self->get_type = get_type;
}
