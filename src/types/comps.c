/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 21:10:00 by weizhang          #+#    #+#             */
/*   Updated: 2026/08/08 21:10:00 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "datastructures.h"
#include "minirt.h"
#include "tuple.h"

t_comps	prepare_computations(t_intersection inter, t_ray r)
{
	t_comps	ret;

	ret.t = inter.t;
	ret.shape = inter.shape;
	ret.p = ray_at(r, ret.t);
	ret.eyev = tuple_scal_mult(r.dir, -1);
	ret.normalv = world_normal_at(ret.shape, ret.p);
	if (tuple_dot(ret.normalv, ret.eyev) < 0)
	{
		ret.inside = true;
		ret.normalv = tuple_scal_mult(ret.normalv, -1);
	}
	else
		ret.inside = false;
	ret.over_point = tuple_add(ret.p, tuple_scal_mult(ret.normalv, EPSILON));
	return (ret);
}

t_rgb	shade_hit(const t_conf *conf, t_comps comps)
{
	t_rgb		am;
	t_rgb		ret;
	t_material	material;
	size_t		i;

	material = comps.shape->material;
	am = color_mult(material.rgb, conf->am.rgb);
	ret = color_scal_mult(am, material.ambient * conf->am.ratio);
	i = 0;
	while (i < conf->lights->len)
	{
		ret = color_add(ret,
				lighting(conf, material, conf->lights->arr[i], comps));
		i++;
	}
	return (ret);
}
