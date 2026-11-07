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

#include <arm_neon.h>
#include "tuple.h"

t_tuple	point(double x, double y, double z)
{
	return ((t_tuple){{x, y, z, 1}});
}

t_tuple	tuple_scal_div(t_tuple t, double scale)
{
	return (tuple_scal_mult(t, 1.0 / scale));
}

/* vmulq_n_f64: 向量的每个通道都乘同一个标量 */
t_tuple	tuple_scal_mult(t_tuple t, double scale)
{
	t_tuple	ret;

	vst1q_f64(ret.arr, vmulq_n_f64(vld1q_f64(t.arr), scale));
	vst1q_f64(ret.arr + 2, vmulq_n_f64(vld1q_f64(t.arr + 2), scale));
	return (ret);
}

t_tuple	tuple_sub(t_tuple t1, t_tuple t2)
{
	t_tuple	ret;

	vst1q_f64(ret.arr, vsubq_f64(vld1q_f64(t1.arr), vld1q_f64(t2.arr)));
	vst1q_f64(ret.arr + 2,
		vsubq_f64(vld1q_f64(t1.arr + 2), vld1q_f64(t2.arr + 2)));
	return (ret);
}

t_tuple	vector(double x, double y, double z)
{
	return ((t_tuple){{x, y, z, 0}});
}
