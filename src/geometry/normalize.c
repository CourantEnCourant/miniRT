/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 19:52:26 by weizhang          #+#    #+#             */
/*   Updated: 2026/08/04 19:52:28 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "tuple.h"

t_tuple quadric_normal_at(t_tuple local, double y_min, double y_max,
        bool has_bottom, double dfdy)
{
    if (local.arr[Y] >= y_max -1e-6)
        return (vector(0, 1, 0));
    if (has_bottom && local.arr[Y] <= y_min + 1e-6)
        return (vector(0, -1, 0));
    return (tuple_normalize(vector(2 * local.arr[X], -dfdy,
                2 * local.arr[Z])));
}

