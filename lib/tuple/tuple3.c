/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 22:42:05 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/23 22:42:13 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "tuple.h"

t_tuple	tuple_hadamar(t_tuple t1, t_tuple t2)
{
	return ((t_tuple){{t1.arr[X] * t2.arr[X],
			t1.arr[Y] * t2.arr[Y],
			t1.arr[Z] * t2.arr[Z],
			t1.arr[W] * t2.arr[W]}});
}

bool	tuple_eq(t_tuple t1, t_tuple t2)
{
	size_t	i;

	i = 0;
	while (i < 4)
	{
		if (!deq(t1.arr[i], t2.arr[i]))
			return (false);
		i++;
	}
	return (true);
}
