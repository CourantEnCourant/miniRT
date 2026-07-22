/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 18:36:21 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/22 18:36:59 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vec3	vec3_scal_mult(t_vec3 v1, double scale)
{
	return ((t_vec3){{v1.arr[X] * scale,
			v1.arr[Y] * scale,
			v1.arr[Z] * scale}});
}

t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){{v1.arr[X] - v2.arr[X],
			v1.arr[Y] - v2.arr[Y],
			v1.arr[Z] - v2.arr[Z]}});
}

t_vec3	vec3_scal_div(t_vec3 v, double scale)
{
	return (vec3_scal_mult(v, 1.0 / scale));
}
