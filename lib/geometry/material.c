/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 01:32:47 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/26 01:34:30 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

t_material	default_material(void)
{
	t_material	ret;

	ret.color = color(1, 1, 1);
	ret.ambient = 0.1;
	ret.diffuse = 0.9;
	ret.specular = 0.9;
	ret.shininess = 200.0;
	return (ret);
}
