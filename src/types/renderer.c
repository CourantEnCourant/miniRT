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
#include <sys/time.h>
#include "libft.h"
#include "mlx.h"
#include "minirt.h"

static inline void	put_pixel(char *dst, t_rgb rgb)
{
	*(unsigned int *)dst = rgb_to_int(rgb);
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

void	render(const t_renderer *self, const t_conf *conf)
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
