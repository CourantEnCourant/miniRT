/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 19:28:42 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/14 19:30:08 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

unsigned int	rgb_to_int(t_rgb rgb)
{
	return ((unsigned int)rgb.arr[R] << 16
		| (unsigned int)rgb.arr[G] << 8
		| (unsigned int)rgb.arr[B]);
}
