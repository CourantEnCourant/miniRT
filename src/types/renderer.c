/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 22:17:07 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/13 22:26:15 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include "gc.h"
#include "mlx.h"
#include "minirt.h"
#include "tuple.h"

static inline void	put_pixel(char *dst, t_rgb rgb)
{
	*(unsigned int *)dst = rgb_to_int(rgb);
}

static bool	is_shadowed(const t_conf *conf, t_tuple p, const t_light *light)
{
	t_tuple			v;
	t_ray			r;
	t_xs			xs;
	t_intersection	h;
	double			distance;

	v = tuple_sub(light->coord, p);
	distance = tuple_mod(v);
	r.orig = p;
	r.dir = tuple_normalize(v);
	xs = intersect_world(r, conf);
	h = hit(&xs);
	return (h.shape && h.t < distance);
}

static t_rgb	lighting(const t_conf *conf, t_material material,
	const t_light *light, t_comps comps)
{
	t_rgb	diffuse;
	t_rgb	specular;
	t_tuple	lightv;
	double	light_dot_normal;

	lightv = tuple_normalize(tuple_sub(light->coord, comps.over_point));
	light_dot_normal = tuple_dot(lightv, comps.normalv);
	if (light_dot_normal < 0)
		return (color(0, 0, 0));
	if (is_shadowed(conf, comps.over_point, light))
		return (color(0, 0, 0));
	diffuse = color_scal_mult(color_mult(material.rgb, light->rgb),
			material.diffuse * light->brightness * light_dot_normal);
	t_tuple reflectv = reflect(tuple_scal_mult(lightv, -1), comps.normalv);
	double reflect_dot_eye = tuple_dot(reflectv, comps.eyev);
	if (reflect_dot_eye <= 0)
		specular = color(0, 0, 0);
	else
	{
		double factor = pow(reflect_dot_eye, material.shininess);
		specular = tuple_scal_mult(light->rgb, material.specular * light->brightness * factor);
	}
	return (color_add(diffuse, specular));
}

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
		ret = color_add(ret, lighting(conf, material, conf->lights->arr[i], comps));
		i++;
	}
	return (ret);
}

static t_rgb	ray_color(t_ray r, const t_conf *conf)
{
	t_xs			xs;
	t_intersection	inter;

	xs = intersect_world(r, conf);
	inter = hit(&xs);
	if (!inter.shape)
		return (color(0, 0, 0));
	return (shade_hit(conf, prepare_computations(inter, r)));
}

static void	render_frame(const t_renderer *self, const t_conf *conf)
{
	const int	bpp = self->bits_per_pixel / 8;
	char		*row;
	char		*px;
	size_t		x;
	size_t		y;

	row = self->addr;
	y = 0;
	while (y < WIN_H)
	{
		px = row;
		x = 0;
		while (x < WIN_W)
		{
			put_pixel(px, ray_color(ray_for_pixel(&conf->camera, x, y), conf));
			px += bpp;
			x++;
		}
		row += self->line_length;
		y++;
	}
}

static void	render(const t_renderer *self, const t_conf *conf)
{
	render_frame(self, conf);
	mlx_put_image_to_window(self->mlx, self->mlx_win, self->img, 0, 0);
	mlx_loop(self->mlx);
}

static int	close_window(t_renderer *renderer)
{
	dest_conf(renderer->conf);
	dest_renderer(renderer);
	dest_gc(renderer->gc);
	exit(0);
}

static int	key_hook(int keycode, void *param)
{
	if (keycode == KEY_ESC)
		close_window(param);
	return (0);
}

void	init_renderer(t_renderer *self, t_conf *conf, t_gc *gc)
{
	self->mlx = mlx_init();
	self->mlx_win = mlx_new_window(self->mlx, WIN_W, WIN_H, "window");
	self->img = mlx_new_image(self->mlx, WIN_W, WIN_H);
	self->addr = mlx_get_data_addr(self->img, &self->bits_per_pixel,
			&self->line_length, &self->endian);
	self->conf = conf;
	self->gc = gc;
	self->render = render;
	mlx_key_hook(self->mlx_win, key_hook, self);
	mlx_hook(self->mlx_win, EVENT_DESTROY, MASK_DESTROY,
		(t_fn)(intptr_t)close_window, self);
}

void	dest_renderer(t_renderer *self)
{
	mlx_destroy_image(self->mlx, self->img);
	mlx_destroy_window(self->mlx, self->mlx_win);
	// linux only
	// mlx_destroy_display(self->mlx);
	free(self->mlx);
}
