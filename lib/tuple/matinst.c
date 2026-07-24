/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matinst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 05:44:43 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/24 05:46:57 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stddef.h>
#include "tuple.h"

t_mat	mat_id(void)
{
	return ((t_mat){{{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}}, 4});
}

t_mat	mat_rotate_x(double radian)
{
	double	cosr;
	double	sinr;

	cosr = cos(radian);
	sinr = sin(radian);
	return ((t_mat){{{1, 0, 0, 0},
		{0, cosr, -sinr, 0},
		{0, sinr, cosr, 0},
		{0, 0, 0, 1}}, 4});
}

t_mat	mat_rotate_y(double radian)
{
	double	cosr;
	double	sinr;

	cosr = cos(radian);
	sinr = sin(radian);
	return ((t_mat){{{cosr, 0, sinr, 0},
		{0, 1, 0, 0},
		{-sinr, 0, cosr, 0},
		{0, 0, 0, 1}}, 4});
}

t_mat	mat_rotate_z(double radian)
{
	double	cosr;
	double	sinr;

	cosr = cos(radian);
	sinr = sin(radian);
	return ((t_mat){{{cosr, -sinr, 0, 0},
		{sinr, cosr, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}}, 4});
}

t_mat	mat_scal(double x, double y, double z)
{
	return ((t_mat){{{x, 0, 0, 0},
		{0, y, 0, 0},
		{0, 0, z, 0},
		{0, 0, 0, 1}}, 4});
}
