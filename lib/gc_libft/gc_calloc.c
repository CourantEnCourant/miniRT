/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 16:03:09 by weizhang          #+#    #+#             */
/*   Updated: 2026/02/03 13:25:52 by weiqi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "gc_libft.h"
#include "libft.h"

void	*gc_calloc(size_t nmemb, size_t size, t_gc *gc)
{
	void	*arr;

	arr = ft_calloc(nmemb, size);
	if (!arr)
	{
		dest_gc(gc);
		exit(EXIT_FAILURE);
	}
	gc->add(gc, arr);
	return (arr);
}
