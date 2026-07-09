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

#include <stdbool.h>
#include <stddef.h>
#include "datastructures.h"
#include "gc.h"

size_t	find_i(const t_darray *s,
		bool (*f)(const void *e1, const void *e2),
		const void *e2)
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

const void	*find(const t_darray *s,
		bool (*f)(const void *e1, const void *e2),
		const void *e2)
{
	size_t	i;

	i = find_i(s, f, e2);
	if (i == s->len)
		return (NULL);
	return (s->peek_i(s, i));
}

bool	any(const t_darray *s,
		bool (*f)(const void *e1, const void *e2),
		const void *e2)
{
	return (find_i(s, f, e2) != s->len);
}

t_darray	*filter(const t_darray *s,
		bool (*f)(const void *e1, const void *e2),
		void *(*copy)(const void *org, t_gc *gc),
		const void *e2)
{
	t_darray	*filtered;
	size_t		i;

	filtered = new_darray(s->gc);
	i = 0;
	while (i < s->len)
	{
		if (f(s->arr[i], e2))
		{
			if (copy)
				filtered->push(filtered, copy(s->arr[i], s->gc));
			else
				filtered->push(filtered, s->arr[i]);
		}
		i++;
	}
	return (filtered);
}

void	*reduce(const t_darray *s,
		void *(*f)(const void *, const void *, t_gc *),
		void *a,
		void (*dest)(void *, t_gc *))
{
	size_t	i;
	void	*tmp;

	i = 0;
	while (i < s->len)
	{
		tmp = f(a, s->arr[i], s->gc);
		if (dest && tmp != a)
			dest(a, s->gc);
		a = tmp;
		i++;
	}
	return (a);
}
