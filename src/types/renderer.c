/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 22:17:07 by weizhang          #+#    #+#             */
/*   Updated: 2026/11/07 09:43:37 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include "libft.h"
#include "mlx.h"
#include "minirt.h"
#include "thread.h"

static inline void	put_pixel(char *dst, t_rgb rgb)
{
	*(unsigned int *)dst = rgb_to_int(rgb);
}

static void	*routine(void *ptr)
{
	int			bpp;
	char		*px;
	size_t		x;
	t_thread	*thread;

	thread = ptr;
	bpp = thread->renderer->bits_per_pixel / 8;
	for (size_t y = thread->i; y < WIN_H; y += thread->thread_count)
	{
		px = thread->renderer->addr + y * thread->renderer->line_length;
		x = 0;
		while (x < WIN_W)
		{
			put_pixel(px, ray_color(ray_for_pixel(&thread->conf->camera, x, y), thread->conf));
			px += bpp;
			x++;
		}
	}
	return (NULL);
}

static int	elapsed_ms(struct timeval start, struct timeval end)
{
	return ((end.tv_sec - start.tv_sec) * 1000
		+ (end.tv_usec - start.tv_usec) / 1000);
}

static void	render_frame(const t_renderer *self, const t_conf *conf)
{
	t_thread	*pool;
	long		thread_count;
	struct timeval	start;
	struct timeval	end;

	thread_count = sysconf(_SC_NPROCESSORS_ONLN);
	ft_printf("Working with %d threads\n", thread_count);
	pool = malloc(sizeof(t_thread) * thread_count);
	for (long i = 0; i < thread_count; ++i)
		init_thread(&pool[i], i, thread_count, self, conf);
	gettimeofday(&start, NULL);
	for (long i = 0; i < thread_count; ++i)
		pthread_create(&pool[i].thread, NULL, routine, &pool[i]);
	for (long i = 0; i < thread_count; ++i)
		pthread_join(pool[i].thread, NULL);
	gettimeofday(&end, NULL);
	ft_printf("Rendered in %d ms\n", elapsed_ms(start, end));
	free(pool);
}

void	render(const t_renderer *self, const t_conf *conf)
{
	render_frame(self, conf);
	mlx_put_image_to_window(self->mlx, self->mlx_win, self->img, 0, 0);
	mlx_loop(self->mlx);
}
