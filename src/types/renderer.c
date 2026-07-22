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
#include "vector.h"

static inline void	put_pixel(char *dst, t_rgb rgb)
{
	*(unsigned int *)dst = normalized_rgb_to_int(rgb);
}

static t_rgb	ray_color(const t_ray *r, const t_sphere *sphere)
{
	if (hit_sphere(r, sphere))
		return ((t_rgb){{1, 0, 0}});
	t_vec3 unit_direction = vec3_normalize(r->dir);
	double a = 0.5 * (unit_direction.arr[Y] + 1.0);
	t_rgb color = vec3_scal_mult((t_rgb){{1, 1, 1}}, 1 - a);
	color = vec3_add(color, vec3_scal_mult((t_rgb){{0.5, 0.7, 1.0}}, a));
	return (color);
}

static void	render_frame(const t_renderer *self, const t_conf *conf)
{
	// Ray tracing in one weekend
    double focal_length = 1.0;
    double viewport_width = 2 * focal_length * tan(conf->camera.hfov_rad / 2);
    double viewport_height = (double)WIN_H / WIN_W * viewport_width;
	t_vec3 viewport_u = {{viewport_width, 0, 0}};
	t_vec3 viewport_v = {{0, -viewport_height, 0}};
	t_vec3 pixel_delta_u = vec3_scal_div(viewport_u, WIN_W);
	t_vec3 pixel_delta_v = vec3_scal_div(viewport_v, WIN_H);
	t_vec3 viewport_upper_left = vec3_sub(conf->camera.coord, (t_vec3){{0, 0, focal_length}});
	viewport_upper_left = vec3_sub(viewport_upper_left, vec3_scal_div(viewport_u, 2));
	viewport_upper_left = vec3_sub(viewport_upper_left, vec3_scal_div(viewport_v, 2));
	t_vec3 pixel00_loc = vec3_add(viewport_upper_left, vec3_scal_mult(vec3_add(pixel_delta_u, pixel_delta_v), 0.5));

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
			t_vec3 pixel_center = vec3_add(pixel00_loc, vec3_add(vec3_scal_mult(pixel_delta_u, x), vec3_scal_mult(pixel_delta_v, y)));
			t_vec3 ray_direction = vec3_sub(pixel_center, conf->camera.coord);
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
