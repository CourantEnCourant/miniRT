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
#include "libft.h"

void	*peek_i(t_darray *self, size_t i)
{
	if (i >= self->len)
	{
		ft_dprintf(STDERR_FILENO,
				"IndexError: max len is %d, peeked at %d\n", self->len, i);
		return (NULL);
	}
	return (self->arr[i]);
}

void	*peek(t_darray *self)
{
	if (self->len == 0)
	{
		ft_dprintf(STDERR_FILENO,
				"IndexError: peeked from empty darray\n");
		return (NULL);
	}
	return (peek_i(self, self->len - 1));
}

void	set(t_darray *self, size_t i, void *item)
{
	if (i + 1 > self->len)
	{
		ft_dprintf(STDERR_FILENO,
			"IndexError: darray len %d while set at %d\n", self->len, i);
		return ;
	}
	self->arr[i] = item;
}
