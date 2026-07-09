/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 19:18:22 by weizhang          #+#    #+#             */
/*   Updated: 2026/02/07 02:21:45 by weiqizhang       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include "gc_libft.h"
#include "libft.h"

char	*gc_get_next_line(int fd, t_gc *gc)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	gc->add(gc, line);
	return (line);
}
