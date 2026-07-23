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

static t_rgb	ray_color(const t_ray *r, const t_sphere *sphere)
{
	double	t;

	t = hit_sphere(r, sphere);
	if (t > 0.0)
	{
		t_tuple normal = tuple_normalize(tuple_sub(ray_at(r, t), sphere->base.coord));
		t_rgb ret = vector(normal.arr[X] + 1, normal.arr[Y] + 1, normal.arr[Z] + 1);
		return (tuple_scal_mult(ret, 0.5));
	}
	t_tuple unit_direction = tuple_normalize(r->dir);
	double a = 0.5 * (unit_direction.arr[Y] + 1.0);
	t_rgb color = tuple_scal_mult(vector(1, 1, 1), 1 - a);
	color = tuple_add(color, tuple_scal_mult(vector(0.5, 0.7, 1.0), a));
	return (color);
}

static void	render_frame(const t_renderer *self, const t_conf *conf)
{
	// Ray tracing in one weekend
    double focal_length = 1.0;
    double viewport_width = 2 * focal_length * tan(conf->camera.hfov_rad / 2);
    double viewport_height = (double)WIN_H / WIN_W * viewport_width;
	t_tuple viewport_u = vector(viewport_width, 0, 0);
	t_tuple viewport_v = vector(0, -viewport_height, 0);
	t_tuple pixel_delta_u = tuple_scal_div(viewport_u, WIN_W);
	t_tuple pixel_delta_v = tuple_scal_div(viewport_v, WIN_H);
	t_tuple viewport_upper_left = tuple_sub(conf->camera.coord, vector(0, 0, focal_length));
	viewport_upper_left = tuple_sub(viewport_upper_left, tuple_scal_div(viewport_u, 2));
	viewport_upper_left = tuple_sub(viewport_upper_left, tuple_scal_div(viewport_v, 2));
	t_tuple pixel00_loc = tuple_add(viewport_upper_left, tuple_scal_mult(tuple_add(pixel_delta_u, pixel_delta_v), 0.5));

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
			t_tuple pixel_center = tuple_add(pixel00_loc, tuple_add(tuple_scal_mult(pixel_delta_u, x), tuple_scal_mult(pixel_delta_v, y)));
			t_tuple ray_direction = tuple_sub(pixel_center, conf->camera.coord);
			t_ray r = {conf->camera.coord, ray_direction};
			put_pixel(px, ray_color(&r, conf->shapes->arr[0]));
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

void	init_renderer(t_renderer *self, t_gc *gc)
{
	self->mlx = mlx_init();
	self->mlx_win = mlx_new_window(self->mlx, WIN_W, WIN_H, "window");
	self->img = mlx_new_image(self->mlx, WIN_W, WIN_H);
	self->addr = mlx_get_data_addr(self->img, &self->bits_per_pixel,
			&self->line_length, &self->endian);
	self->gc = gc;
	self->render = render;
}

void	dest_renderer(t_renderer *self)
{
	mlx_destroy_image(self->mlx, self->img);
	mlx_destroy_window(self->mlx, self->mlx_win);
	// linux only
	// mlx_destroy_display(self->mlx);
	free(self->mlx);
}
