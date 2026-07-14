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

static inline void	put_pixel(char *dst, t_rgb rgb)
{
	*(unsigned int *)dst = rgb_to_int(rgb);
}

static inline t_rgb	compute_color(size_t x, size_t y)
{
	t_rgb	rgb;

	rgb.r = (unsigned char)(255.999 * ((double)x / (WIN_W - 1)));
	rgb.g = (unsigned char)(255.999 * ((double)y / (WIN_H - 1)));
	rgb.b = 0;
	return (rgb);
}

static void	render_frame(const t_renderer *self)
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
			put_pixel(px, compute_color(x, y));
			px += bpp;
			x++;
		}
		row += self->line_length;
		y++;
	}
}

static void	render(const t_renderer *self)
{
	render_frame(self);
	mlx_put_image_to_window(self->mlx, self->mlx_win, self->img, 0, 0);
	mlx_loop(self->mlx);
}

void	init_renderer(t_renderer *self, t_gc *gc)
{
	self->mlx = mlx_init();
	self->mlx_win = mlx_new_window(self->mlx, 800, 600, "window");
	self->img = mlx_new_image(self->mlx, 800, 600);
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
