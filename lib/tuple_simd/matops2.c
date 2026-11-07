/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matops2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 05:44:43 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/24 06:57:30 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arm_neon.h>
#include <stddef.h>
#include "tuple.h"

/*
** 第 i 行结果 = A[i][0]*B第0行 + A[i][1]*B第1行 + A[i][2]*B第2行 + A[i][3]*B第3行
** 每一行拆成 lo/hi 两半，用 vfmaq_n_f64 (乘标量再累加) 逐行累积
** 只支持 4x4 (项目里所有 mat_mul 调用都是 4x4)
*/
t_mat	mat_mul(t_mat A, t_mat B)
{
	t_mat		ret;
	float64x2_t	lo;
	float64x2_t	hi;
	size_t		i;
	size_t		k;

	i = -1;
	while (++i < 4)
	{
		lo = vdupq_n_f64(0);
		hi = vdupq_n_f64(0);
		k = -1;
		while (++k < 4)
		{
			lo = vfmaq_n_f64(lo, vld1q_f64(B.arr[k]), A.arr[i][k]);
			hi = vfmaq_n_f64(hi, vld1q_f64(B.arr[k] + 2), A.arr[i][k]);
		}
		vst1q_f64(ret.arr[i], lo);
		vst1q_f64(ret.arr[i] + 2, hi);
	}
	ret.size = 4;
	return (ret);
}

/* 每个分量 = A 的第 i 行 · t，就是 4 次 dot product */
t_tuple	mat_mul_tuple(const t_mat *A, t_tuple t)
{
	t_tuple		ret;
	float64x2_t	lo;
	float64x2_t	hi;
	float64x2_t	acc;
	size_t		i;

	lo = vld1q_f64(t.arr);
	hi = vld1q_f64(t.arr + 2);
	i = 0;
	while (i < 4)
	{
		acc = vmulq_f64(vld1q_f64(A->arr[i]), lo);
		acc = vfmaq_f64(acc, vld1q_f64(A->arr[i] + 2), hi);
		ret.arr[i] = vaddvq_f64(acc);
		i++;
	}
	return (ret);
}

t_mat	mat_subm(t_mat A, size_t row, size_t col)
{
	t_mat	ret;
	size_t	i;
	size_t	j;

	i = 0;
	while (i < A.size)
	{
		j = 0;
		while (j < A.size)
		{
			if (i != row && j != col)
				ret.arr[i - (i > row)][j - (j > col)] = A.arr[i][j];
			j++;
		}
		i++;
	}
	ret.size = A.size - 1;
	return (ret);
}

t_mat	mat_scal_mult(t_mat A, double scale)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < A.size)
	{
		j = 0;
		while (j < A.size)
		{
			A.arr[i][j] = A.arr[i][j] * scale;
			j++;
		}
		i++;
	}
	return (A);
}

t_mat	mat_t(t_mat A)
{
	t_mat	ret;
	size_t	i;
	size_t	j;

	i = 0;
	while (i < A.size)
	{
		j = 0;
		while (j < A.size)
		{
			ret.arr[j][i] = A.arr[i][j];
			j++;
		}
		i++;
	}
	ret.size = A.size;
	return (ret);
}
