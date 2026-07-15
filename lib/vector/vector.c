/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 01:24:45 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/10 01:49:33 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	cross_product(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){{v1.arr[Y] * v2.arr[Z] - v1.arr[Z] * v2.arr[Y],
			v1.arr[Z] * v2.arr[X] - v1.arr[X] * v2.arr[Z],
			v1.arr[X] * v2.arr[Y] - v1.arr[Y] * v2.arr[X]}});
}

double	dot_product(t_vec3 v1, t_vec3 v2)
{
	return (v1.arr[X] * v2.arr[X]
		+ v1.arr[Y] * v2.arr[Y]
		+ v1.arr[Z] * v2.arr[Z]);
}

t_vec3	vec3_add(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){{v1.arr[X] + v2.arr[X],
			v1.arr[Y] + v2.arr[Y],
			v1.arr[Z] + v2.arr[Z]}});
}

t_vec3	vec3_scal_mult(t_vec3 v1, double scale)
{
	return ((t_vec3){{v1.arr[X] * scale,
			v1.arr[Y] * scale,
			v1.arr[Z] * scale}});
}
