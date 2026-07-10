/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dllist.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 06:19:59 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/07 06:56:39 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "gc.h"

t_dllist	*new_dllist(void *content)
{
	t_dllist	*node;

	node = malloc(sizeof(t_dllist));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	dllist_add_front(t_dllist **lst, t_dllist *node)
{
	if (!lst || !node)
		return ;
	node->prev = NULL;
	node->next = *lst;
	if (*lst)
		(*lst)->prev = node;
	*lst = node;
}

t_dllist	*find_dllist(t_dllist *self, void *content)
{
	while (self)
	{
		if (self->content == content)
			return (self);
		self = self->next;
	}
	return (NULL);
}

void	del_dllist(t_dllist *self, void (*del)(void *))
{
	if (self->prev)
		self->prev->next = self->next;
	if (self->next)
		self->next->prev = self->prev;
	del(self->content);
	free(self);
}

void	clear_dllist(t_dllist *self, void (*del)(void *))
{
	t_dllist	*next;

	while (self)
	{
		next = self->next;
		del(self->content);
		free(self);
		self = next;
	}
}
