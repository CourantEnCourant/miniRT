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
#include "vector.h"

void	init_shape(t_shape *self, enum e_type type, t_vec3 coord, t_rgb rgb)
{
	self->type = type;
	self->coord = coord;
	self->rgb = rgb;
}
