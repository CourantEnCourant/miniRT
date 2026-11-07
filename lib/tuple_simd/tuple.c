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

#include <arm_neon.h>
#include <math.h>
#include "tuple.h"

/*
** t_tuple 是 4 个 double = 256 bit，NEON 寄存器只有 128 bit (2 个 double)
** 所以每个 tuple 拆成两半: lo = {x, y}, hi = {z, w}
*/

t_tuple	cross_product(t_tuple t1, t_tuple t2)
{
	return ((t_tuple){{t1.arr[Y] * t2.arr[Z] - t1.arr[Z] * t2.arr[Y],
			t1.arr[Z] * t2.arr[X] - t1.arr[X] * t2.arr[Z],
			t1.arr[X] * t2.arr[Y] - t1.arr[Y] * t2.arr[X],
			0}});
}

t_tuple	tuple_add(t_tuple t1, t_tuple t2)
{
	t_tuple	ret;

	vst1q_f64(ret.arr, vaddq_f64(vld1q_f64(t1.arr), vld1q_f64(t2.arr)));
	vst1q_f64(ret.arr + 2,
		vaddq_f64(vld1q_f64(t1.arr + 2), vld1q_f64(t2.arr + 2)));
	return (ret);
}

/*
** lo1*lo2 -> {x1x2, y1y2}
** fma 加上 hi1*hi2 -> {x1x2 + z1z2, y1y2 + w1w2}
** vaddvq 把两个通道横向相加 -> 标量
*/
double	tuple_dot(t_tuple t1, t_tuple t2)
{
	float64x2_t	acc;

	acc = vmulq_f64(vld1q_f64(t1.arr), vld1q_f64(t2.arr));
	acc = vfmaq_f64(acc, vld1q_f64(t1.arr + 2), vld1q_f64(t2.arr + 2));
	return (vaddvq_f64(acc));
}

double	tuple_mod(t_tuple t)
{
	return (sqrt(tuple_dot(t, t)));
}

t_tuple	tuple_normalize(t_tuple t)
{
	return (tuple_scal_div(t, tuple_mod(t)));
}
