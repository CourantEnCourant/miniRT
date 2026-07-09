/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_io_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 19:44:33 by weizhang          #+#    #+#             */
/*   Updated: 2026/03/24 19:45:35 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "datastructures.h"
#include "gc.h"
#include "libft.h"

const void	*peek_i(const t_darray *self, size_t i)
{
	if (i >= self->len)
	{
		ft_dprintf(STDERR_FILENO,
			"IndexError: max len is %d, peeked at %d\n", self->len, i);
		return (NULL);
	}
	return (self->arr[i]);
}

const void	*peek(const t_darray *self)
{
	if (self->len == 0)
	{
		ft_dprintf(STDERR_FILENO,
			"IndexError: peeked from empty darray\n");
		return (NULL);
	}
	return (self->arr[self->len - 1]);
}

void	set(t_darray *self,
		size_t i,
		const void *item,
		void (*dest)(void *, t_gc *))
{
	if (i + 1 > self->len)
	{
		ft_dprintf(STDERR_FILENO,
			"IndexError: darray len %d while set at %d\n", self->len, i);
		return ;
	}
	if (dest && item != self->arr[i])
		dest(self->arr[i], self->gc);
	self->arr[i] = (void *)item;
}

void	repr(const t_darray *self, void (*repr_item)(const void *value))
{
	size_t	i;

	write(1, "[", 1);
	i = 0;
	if (!self->len)
	{
		write(1, "]\n", 2);
		return ;
	}
	while (i < self->len - 1)
	{
		repr_item(self->arr[i]);
		write(1, ", ", 2);
		i++;
	}
	repr_item(self->arr[i]);
	write(1, "]\n", 2);
}
