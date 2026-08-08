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
	self->material = default_material();
	self->material.rgb = rgb;
}

void	set_matrices(t_shape *self, t_mat transform)
{
	self->transform = transform;
	self->transform_inv = mat_inv(transform);
	self->transform_inv_t = mat_t(self->transform_inv);
}

t_tuple	world_normal_at(const t_shape *self, t_tuple p)
{
	t_tuple	normal;

	normal = self->local_normal_at(self, mat_mul_tuple(&self->transform_inv, p));
	normal = mat_mul_tuple(&self->transform_inv_t, normal);
	normal.arr[W] = 0;
	return (tuple_normalize(normal));
}
