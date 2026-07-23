/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 18:36:21 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/23 00:00:00 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"

t_tuple	point(double x, double y, double z)
{
	return ((t_tuple){{x, y, z, 1}});
}

t_tuple	tuple_scal_div(t_tuple t, double scale)
{
	return (tuple_scal_mult(t, 1.0 / scale));
}

t_tuple	tuple_scal_mult(t_tuple t, double scale)
{
	return ((t_tuple){{t.arr[X] * scale,
			t.arr[Y] * scale,
			t.arr[Z] * scale,
			t.arr[W] * scale}});
}

t_tuple	tuple_sub(t_tuple t1, t_tuple t2)
{
	return ((t_tuple){{t1.arr[X] - t2.arr[X],
			t1.arr[Y] - t2.arr[Y],
			t1.arr[Z] - t2.arr[Z],
			t1.arr[W] - t2.arr[W]}});
}

t_tuple	vector(double x, double y, double z)
{
	return ((t_tuple){{x, y, z, 0}});
}
