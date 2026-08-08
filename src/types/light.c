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

#include <math.h>
#include <stdbool.h>
#include "datastructures.h"
#include "gc.h"
#include "libft.h"
#include "minirt.h"
#include "tuple.h"

static t_light	*new_light(t_tuple coord, double brightness, t_rgb rgb,
	t_gc *gc)
{
	t_light	*ret;

	ret = gc_malloc(sizeof(t_light), gc);
	ret->coord = coord;
	ret->brightness = brightness;
	ret->rgb = rgb;
	return (ret);
}

bool	add_light(t_darray *lights, t_darray *param)
{
	t_tuple	coord;
	double	brightness;
	t_rgb	rgb;

	if (param->len != 4)
		return (false);
	if (!parse_coord(&coord, param->arr[1], param->gc))
		return (false);
	brightness = ft_atof(param->arr[2]);
	if (brightness < 0 || brightness > 1)
		return (false);
	if (!parse_rgb(&rgb, param->arr[3], param->gc))
		return (false);
	lights->push(lights, new_light(coord, brightness, rgb, lights->gc));
	return (true);
}

static bool	is_shadowed(const t_conf *conf, t_tuple p, t_tuple lightv,
	double distance)
{
	t_ray	r;

	r.orig = p;
	r.dir = lightv;
	return (shadow_hit(conf, r, distance));
}

static t_rgb	specular_of(t_material material, const t_light *light,
	t_comps comps, t_tuple lightv)
{
	t_tuple	reflectv;
	double	reflect_dot_eye;
	double	factor;

	reflectv = reflect(tuple_scal_mult(lightv, -1), comps.normalv);
	reflect_dot_eye = tuple_dot(reflectv, comps.eyev);
	if (reflect_dot_eye <= 0)
		return (color(0, 0, 0));
	factor = pow(reflect_dot_eye, material.shininess);
	return (color_scal_mult(light->rgb,
			material.specular * light->brightness * factor));
}

t_rgb	lighting(const t_conf *conf, t_material material,
	const t_light *light, t_comps comps)
{
	t_rgb	diffuse;
	t_tuple	lightv;
	double	distance;
	double	light_dot_normal;

	lightv = tuple_sub(light->coord, comps.over_point);
	distance = tuple_mod(lightv);
	lightv = tuple_scal_mult(lightv, 1.0 / distance);
	light_dot_normal = tuple_dot(lightv, comps.normalv);
	if (light_dot_normal < 0)
		return (color(0, 0, 0));
	if (is_shadowed(conf, comps.over_point, lightv, distance))
		return (color(0, 0, 0));
	diffuse = color_scal_mult(color_mult(material.rgb, light->rgb),
			material.diffuse * light->brightness * light_dot_normal);
	return (color_add(diffuse, specular_of(material, light, comps, lightv)));
}
