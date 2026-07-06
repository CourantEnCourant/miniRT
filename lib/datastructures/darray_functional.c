/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_functional.c                                :+:      :+:    :+:   */
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

size_t	find_i(t_darray *s, bool (*f)(void *e1, void *e2), void *e2)
{
	size_t	i;

	i = 0;
	while (i < s->len)
	{
		if (f(s->peek_i(s, i), e2))
			return (i);
		i++;
	}
	return (s->len);
}

void	*find(t_darray *s, bool (*f)(void *e1, void *e2), void *e2)
{
	size_t	i;

	i = find_i(s, f, e2);
	if (i == s->len)
		return (NULL);
	return (s->peek_i(s, i));
}

bool	any(t_darray *s, bool (*f)(void *e1, void *e2), void *e2)
{
	return (find_i(s, f, e2) != s->len);
}

t_darray	*filter(t_darray *s, bool (*f)(void *e1, void *e2), void *e2)
{
	t_darray	*filtered;
	size_t		i;

	filtered = init_darray(s->gc);
	i = 0;
	while (i < s->len)
	{
		if (f(s->peek_i(s, i), e2))
			filtered->push(filtered, s->peek_i(s, i));
		i++;
	}
	return (filtered);
}

void	*reduce(t_darray *s, void *(*f)(void *i1, void *i2, t_gc *gc), void *a)
{
	size_t	i;

	i = 0;
	while (i < s->len)
	{
		a = f(a, s->arr[i], s->gc);
		i++;
	}
	return (a);
}
