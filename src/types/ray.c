/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 21:01:34 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/14 21:03:40 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"

void	init_ray(t_ray *self, t_vec3 orig, t_vec3 dir)
{
	self->orig = orig;
	self->dir = dir;
}

t_vec3	ray_at(const t_ray *ray, double t)
{
	return (vec3_add(ray->orig, vec3_scal_mult(ray->dir, t)));
}