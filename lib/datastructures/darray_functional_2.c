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
#include "gc.h"

void	for_each(t_darray *self,
		void *(*f)(void *, t_gc *),
		void (*dest)(void *, t_gc *))
{
	size_t	i;
	void	*tmp;

	i = 0;
	while (i < self->len)
	{
		tmp = self->arr[i];
		self->arr[i] = f(tmp, self->gc);
		if (dest && self->arr[i] != tmp)
			dest(tmp, self->gc);
		i++;
	}
}
