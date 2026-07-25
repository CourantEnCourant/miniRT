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
	t_xs	xs;
	double	t;

	xs = intersect(r, sphere);
	t = -1.0;
	if (xs.count > 0)
	{
		if (xs.xs[0].t > 0.0)
			t = xs.xs[0].t;
		else if (xs.count > 1 && xs.xs[1].t > 0.0)
			t = xs.xs[1].t;
	}
	if (t > 0.0)
	{
		t_tuple normal = tuple_normalize(tuple_sub(ray_at(r, t), sphere->base.coord));
		t_rgb ret = color(normal.arr[X] + 1, normal.arr[Y] + 1, normal.arr[Z] + 1);
		return (color_scal_mult(ret, 0.5));
	}
	return (color(0, 0, 0));
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
