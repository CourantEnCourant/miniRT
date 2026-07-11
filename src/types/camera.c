/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 23:14:10 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/11 23:24:07 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "minirt.h"
#include "vector.h"

bool	camera_is_valid(const t_camera *self)
{
	return (0.0 <= self->normal.arr[X] && self->normal.arr[X] <= 1.0 &&
			0.0 <= self->normal.arr[Y] && self->normal.arr[Y] <= 1.0 &&
			0.0 <= self->normal.arr[Z] && self->normal.arr[Z] <= 1.0 &&
			0.0 <= self->fov && self->fov <= 180);
}
