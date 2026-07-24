/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matops.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 05:44:43 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/24 06:56:27 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include "tuple.h"

double	mat_cofactor(t_mat A, size_t row, size_t col)
{
	int	sign;

	if ((col + row) % 2 == 0)
		sign = 1;
	else
		sign = -1;
	return (sign * mat_minor(A, row, col));
}

double	mat_det(t_mat A)
{
	size_t	i;
	double	ret;

	if (A.size == 2)
		return (A.arr[0][0] * A.arr[1][1]
				- A.arr[0][1] * A.arr[1][0]);
	else
	{
		ret = 0;
		i = 0;
		while (i < A.size)
		{
			ret += A.arr[0][i] * mat_cofactor(A, 0, i);
			i++;
		}
	}
	return (ret);
}

bool	mat_eq(t_mat A, t_mat B)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < A.size)
	{
		j = 0;
		while (j < A.size)
		{
			if (!deq(A.arr[i][j], B.arr[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

t_mat	mat_inv(t_mat A)
{
	t_mat	ret;
	double	det;
	size_t	i;
	size_t	j;

	det = mat_det(A);
	if (deq(det, 0))
	{
		ret.size = 0;
		return (ret);
	}
	i = 0;
	while (i < A.size)
	{
		j = 0;
		while (j < A.size)
		{
			ret.arr[i][j] = mat_cofactor(A, i, j);
			j++;
		}
		i++;
	}
	ret = mat_scal_mult(mat_t(ret), 1 / det);
	ret.size = A.size;
	return (ret);
}

double	mat_minor(t_mat A, size_t row, size_t col)
{
	return (mat_det(mat_subm(A, row, col)));
}
