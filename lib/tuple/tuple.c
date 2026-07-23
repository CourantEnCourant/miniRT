/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 01:24:45 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/23 00:00:00 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "tuple.h"

t_tuple	cross_product(t_tuple t1, t_tuple t2)
{
	return ((t_tuple){{t1.arr[Y] * t2.arr[Z] - t1.arr[Z] * t2.arr[Y],
			t1.arr[Z] * t2.arr[X] - t1.arr[X] * t2.arr[Z],
			t1.arr[X] * t2.arr[Y] - t1.arr[Y] * t2.arr[X],
			0}});
}

t_tuple	tuple_add(t_tuple t1, t_tuple t2)
{
	return ((t_tuple){{t1.arr[X] + t2.arr[X],
			t1.arr[Y] + t2.arr[Y],
			t1.arr[Z] + t2.arr[Z],
			t1.arr[W] + t2.arr[W]}});
}

double	tuple_dot(t_tuple t1, t_tuple t2)
{
	return (t1.arr[X] * t2.arr[X]
		+ t1.arr[Y] * t2.arr[Y]
		+ t1.arr[Z] * t2.arr[Z]
		+ t1.arr[W] * t2.arr[W]);
}

double	tuple_mod(t_tuple t)
{
	return (sqrt(tuple_dot(t, t)));
}

t_tuple	tuple_normalize(t_tuple t)
{
	return (tuple_scal_div(t, tuple_mod(t)));
}
