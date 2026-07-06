/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_basic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:47:31 by weiqi             #+#    #+#             */
/*   Updated: 2026/02/02 20:07:17 by weiqizhang       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "gc_libft.h"
#include "libft.h"

static void	add(t_gc *self, void *item)
{
	t_list	*node;

	node = ft_lstnew(item);
	if (!node)
	{
		free(item);
		self->clean(self);
		exit(EXIT_FAILURE);
	}
	ft_lstadd_front(&self->start, node);
}

static void	clean(t_gc *self)
{
	ft_lstclear(&self->start, free);
	free(self);
}

t_gc	*init_gc(void)
{
	t_gc	*gc;

	gc = malloc(sizeof(t_gc));
	if (!gc)
		exit(EXIT_FAILURE);
	gc->start = NULL;
	gc->clean = clean;
	gc->add = add;
	return (gc);
}
