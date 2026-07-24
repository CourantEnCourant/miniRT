/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matinst2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 05:44:43 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/24 05:46:57 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"

t_mat	mat_shear(double comps[6])
{
	return ((t_mat){{{1, comps[0], comps[1], 0},
		{comps[2], 1, comps[3], 0},
		{comps[4], comps[5], 1, 0},
		{0, 0, 0, 1}}, 4});
}

t_mat	mat_translate(double x, double y, double z)
{
	return ((t_mat){{{1, 0, 0, x},
		{0, 1, 0, y},
		{0, 0, 1, z},
		{0, 0, 0, 1}}, 4});
}
