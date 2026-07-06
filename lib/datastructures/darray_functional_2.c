/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_functional_2.c                                :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 01:21:10 by weizhang          #+#    #+#             */
/*   Updated: 2026/05/09 21:40:59 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "datastructures.h"
#include "gc_libft.h"

void	for_each(t_darray *self, void *(*f)(void *arg, t_gc *gc))
{
	size_t	i;

	i = 0;
	while (i < self->len)
	{
		self->arr[i] = f(self->arr[i], self->gc);
		i++;
	}
}
