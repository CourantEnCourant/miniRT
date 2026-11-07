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

#include <arm_neon.h>
#include "tuple.h"

t_tuple	tuple_hadamar(t_tuple t1, t_tuple t2)
{
	t_tuple	ret;

	vst1q_f64(ret.arr, vmulq_f64(vld1q_f64(t1.arr), vld1q_f64(t2.arr)));
	vst1q_f64(ret.arr + 2,
		vmulq_f64(vld1q_f64(t1.arr + 2), vld1q_f64(t2.arr + 2)));
	return (ret);
}
