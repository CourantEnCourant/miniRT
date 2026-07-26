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
#include "geometry.h"
#include "mlx.h"
#include "minirt.h"
#include "tuple.h"

static inline void	put_pixel(char *dst, t_rgb rgb)
{
	*(unsigned int *)dst = normalized_rgb_to_int(rgb);
}

static t_rgb	lighting(t_material material, t_light light, t_tuple p, t_tuple eyev, t_tuple normalv)
{
	t_rgb	ambient;
	t_rgb	diffuse;
	t_rgb	specular;

	t_rgb effective_color = color_mult(material.color, light.rgb);
	t_tuple lightv = tuple_normalize(tuple_sub(light.coord, p));
	ambient = color_scal_mult(effective_color, material.ambient);
	double light_dot_normal = tuple_dot(lightv, normalv);
	if (light_dot_normal < 0)
	{
		diffuse = color(0, 0, 0);
		specular = color(0, 0, 0);
	}
	else
	{
		diffuse = color_scal_mult(effective_color, material.diffuse * light_dot_normal);
		t_tuple reflectv = reflect(tuple_scal_mult(lightv, -1), normalv);
		double reflect_dot_eye = tuple_dot(reflectv, eyev);
		if (reflect_dot_eye <= 0)
			specular = color(0, 0, 0);
		else
		{
			double factor = pow(reflect_dot_eye, material.shininess);
			specular = tuple_scal_mult(light.rgb, material.specular * factor);
		}
	}
	return (color_add(color_add(ambient, diffuse), specular));
}

t_comps	prepare_computations(t_intersection inter, t_ray r)
{
	t_comps	ret;

	ret.t = inter.t;
	ret.shape = inter.shape;
	ret.p = ray_at(r, ret.t);
	ret.eyev = tuple_scal_mult(r.dir, -1);
	ret.normalv = normal_at((t_sphere *)ret.shape, ret.p);
	if (tuple_dot(ret.normalv, ret.eyev) < 0)
	{
		ret.inside = true;
		ret.normalv = tuple_scal_mult(ret.normalv, -1);
	}
	else
		ret.inside = false;
	return (ret);
}

t_rgb	shade_hit(const t_conf *conf, t_comps comps)
{
	return (lighting(comps.shape->material, conf->light, comps.p, comps.eyev, comps.normalv));
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
	const int		bpp = self->bits_per_pixel / 8;
	const double	ps = 7.0 / WIN_H;
	t_ray			r;
	char			*row;
	char			*px;
	size_t			x;
	size_t			y;

	row = self->addr;
	r.orig = point(0, 0, -5);
	y = 0;
	while (y < WIN_H)
	{
		px = row;
		x = 0;
		while (x < WIN_W)
		{
			r.dir = tuple_normalize(tuple_sub(point(ps * (x - WIN_W / 2.0),
							ps * (WIN_H / 2.0 - y), 10), r.orig));
			put_pixel(px, ray_color(r, conf));
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

void	init_renderer(t_renderer *self, t_gc *gc)
{
	self->mlx = mlx_init();
	self->mlx_win = mlx_new_window(self->mlx, WIN_W, WIN_H, "window");
	self->img = mlx_new_image(self->mlx, WIN_W, WIN_H);
	self->addr = mlx_get_data_addr(self->img, &self->bits_per_pixel,
			&self->line_length, &self->endian);
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
