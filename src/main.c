/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 17:57:26 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/06 17:57:43 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "gc.h"
#include "libft.h"
#include "minirt.h"

bool	endswith(const char *str, const char *end);

static bool	is_valid_conf(const t_conf *conf)
{
	return (conf->am_is_valid && conf->camera_is_valid);
}

int	main(int argc, char *argv[])
{
	int			fd;
	t_gc		*gc;
	t_conf		conf;
	t_renderer	renderer;

	if (argc != 2 || !endswith(argv[1], ".rt"))
		return (ft_dprintf(STDERR_FILENO,
				"Program expects one .rt file as argument\n"), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (ft_dprintf(STDERR_FILENO, "Infile error\n"), 1);
	gc = new_gc();
	if (!init_conf_from_file(&conf, fd, gc) || !is_valid_conf(&conf))
		return (close(fd),
			dest_conf(&conf),
			dest_gc(gc),
			ft_dprintf(STDERR_FILENO, "Error\n"), 1);
	close(fd);
	init_renderer(&renderer, &conf, gc, argv[1]);
	renderer.render(&renderer, &conf);
}
