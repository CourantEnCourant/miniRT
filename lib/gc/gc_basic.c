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
#include "gc.h"

static void	add(t_gc *self, void *item)
{
	t_dllist	*node;

	node = new_dllist(item);
	if (!node)
	{
		free(item);
		dest_gc(self);
		exit(EXIT_FAILURE);
	}
	dllist_add_front(&self->start, node);
}

static void	del(t_gc *self, void *item, void (*del_item)(void *))
{
	t_dllist	*item_node;

	item_node = find_dllist(self->start, item);
	if (!item_node)
		return ;
	if (item_node == self->start)
		self->start = item_node->next;
	del_dllist(item_node, del_item);
}

t_gc	*new_gc(void)
{
	t_gc	*gc;

	gc = malloc(sizeof(t_gc));
	if (!gc)
		exit(EXIT_FAILURE);
	gc->start = NULL;
	gc->add = add;
	gc->del = del;
	return (gc);
}

void	dest_gc(t_gc *gc)
{
	clear_dllist(gc->start, free);
	free(gc);
}
