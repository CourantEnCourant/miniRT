/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 23:14:10 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/21 21:28:03 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>
#include "minirt.h"
#include "tuple.h"

bool	camera_is_valid(const t_camera *self)
{
	return (0.0 <= self->normal.arr[X] && self->normal.arr[X] <= 1.0 &&
			0.0 <= self->normal.arr[Y] && self->normal.arr[Y] <= 1.0 &&
			0.0 <= self->normal.arr[Z] && self->normal.arr[Z] <= 1.0 &&
			0.0 <= self->hfov_rad && self->hfov_rad <= 2 * M_PI);
}
