/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/08 21:10:00 by weizhang          #+#    #+#             */
/*   Updated: 2026/08/08 21:10:00 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include "gc.h"
#include "mlx.h"
#include "minirt.h"

static void	dest_renderer(t_renderer *self)
{
	mlx_destroy_image(self->mlx, self->img);
	mlx_destroy_window(self->mlx, self->mlx_win);
	/* linux only: mlx_destroy_display(self->mlx); */
	free(self->mlx);
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
