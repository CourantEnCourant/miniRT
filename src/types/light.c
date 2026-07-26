/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 23:14:10 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/11 23:19:05 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "gc.h"
#include "geometry.h"
#include "minirt.h"
#include "tuple.h"

t_light	*new_light(t_tuple coord, double brightness, t_rgb rgb, t_gc *gc)
{
	t_light *ret;

	ret = gc_malloc(sizeof(t_light), gc);
	ret->coord = coord;
	ret->brightness = brightness;
	ret->rgb = rgb;
	return (ret);
}
