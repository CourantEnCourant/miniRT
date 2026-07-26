/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 10:07:35 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/09 10:08:41 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"
#include "tuple.h"

void	init_sphere(t_sphere *self, t_tuple coord, t_rgb rgb, double radius)
{
	init_shape(&self->base, SPHERE, coord, rgb);
	self->radius = radius;
	self->base.transform = mat_mul(mat_translate(coord.arr[X], coord.arr[Y], coord.arr[Z]), mat_scal(radius, radius, radius));
}

t_tuple	normal_at(const t_sphere *sp, t_tuple p)
{
	t_tuple	normal;

	p = mat_mul_tuple(mat_inv(sp->base.transform), p);
	normal = tuple_sub(p, point(0, 0, 0));
	normal = mat_mul_tuple(mat_t(mat_inv(sp->base.transform)), normal);
	normal.arr[W] = 0;
	return (tuple_normalize(normal));
}

t_tuple	reflect(t_tuple in, t_tuple normal)
{
	return (tuple_sub(in, tuple_scal_mult(normal, 2 * tuple_dot(in, normal))));
}
