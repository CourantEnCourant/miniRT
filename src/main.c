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

int	main(int argc, char *argv[])
{
	int		fd;
	t_gc	*gc;
	t_conf	conf;

	if (argc != 2 || !endswith(argv[1], ".rt"))
		return (ft_dprintf(STDERR_FILENO,
				"Program expects one .rt file as argument\n"), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (ft_dprintf(STDERR_FILENO, "Infile error\n"), 1);
	gc = new_gc();
	init_conf_from_file(&conf, fd, gc);
	dest_conf(&conf);
	dest_gc(gc);
	close(fd);
}
