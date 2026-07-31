/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 10:07:35 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/09 10:09:45 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "tuple.h"

static const char	*get_type(const t_shape *self)
{
	(void)self;
	return ("plane");
}

void	init_plane(t_plane *self, t_tuple coord, t_rgb rgb, t_tuple normal)
{
	init_shape(&self->base, PLANE, coord, rgb);
	self->normal = normal;
	self->base.get_type = get_type;
}
