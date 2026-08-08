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

#include <stddef.h>
#include "tuple.h"

t_mat	mat_mul(t_mat A, t_mat B)
{
	t_mat	ret;
	size_t	i;
	size_t	j;
	size_t	k;

	i = -1;
	while (++i < A.size)
	{
		j = -1;
		while (++j < A.size)
		{
			k = -1;
			while (++k < A.size)
			{
				ret.arr[i][j] = A.arr[i][0] * B.arr[0][j]
					+ A.arr[i][1] * B.arr[1][j]
					+ A.arr[i][2] * B.arr[2][j]
					+ A.arr[i][3] * B.arr[3][j];
			}
		}
	}
	ret.size = A.size;
	return (ret);
}

t_tuple	mat_mul_tuple(const t_mat *A, t_tuple t)
{
	t_tuple	ret;
	size_t	i;
	size_t	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			ret.arr[i] = t.arr[0] * A->arr[i][0] + t.arr[1] * A->arr[i][1]
				+ t.arr[2] * A->arr[i][2] + t.arr[3] * A->arr[i][3];
			j++;
		}
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
