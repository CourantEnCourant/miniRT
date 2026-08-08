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
#include <sys/time.h>
#include "gc.h"
#include "libft.h"
#include "mlx.h"
#include "minirt.h"
#include "tuple.h"

static inline void	put_pixel(char *dst, t_rgb rgb)
{
	*(unsigned int *)dst = rgb_to_int(rgb);
}

static bool	is_shadowed(const t_conf *conf, t_tuple p, t_tuple lightv,
	double distance)
{
	t_ray	r;

	r.orig = p;
	r.dir = lightv;
	return (shadow_hit(conf, r, distance));
}

static t_rgb	lighting(const t_conf *conf, t_material material,
	const t_light *light, t_comps comps)
{
	t_rgb	diffuse;
	t_rgb	specular;
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
	t_xs	xs;

	intersect_world(&xs, r, conf);
	if (!xs.best.shape)
		return (color(0, 0, 0));
	return (shade_hit(conf, prepare_computations(xs.best, r)));
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

static int	elapsed_ms(struct timeval start, struct timeval end)
{
	return ((end.tv_sec - start.tv_sec) * 1000
		+ (end.tv_usec - start.tv_usec) / 1000);
}

static void	render(const t_renderer *self, const t_conf *conf)
{
	struct timeval	start;
	struct timeval	end;

	gettimeofday(&start, NULL);
	render_frame(self, conf);
	gettimeofday(&end, NULL);
	ft_printf("Rendered in %d ms\n", elapsed_ms(start, end));
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

void	init_renderer(t_renderer *self, t_conf *conf, t_gc *gc,
	const char title[])
{
	self->mlx = mlx_init();
	self->mlx_win = mlx_new_window(self->mlx, WIN_W, WIN_H, (char *)title);
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
