/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_basic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqizhang <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 00:08:35 by weiqizhang        #+#    #+#             */
/*   Updated: 2026/05/11 22:47:17 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "datastructures.h"
#include "gc_libft.h"

bool		any(t_darray *s, bool (*f)(void *, void *), void *e);
t_darray	*filter(t_darray *s, bool (*f)(void *, void *), void *e);
void		*find(t_darray *s, bool (*f)(void *, void *), void *e);
size_t		find_i(t_darray *s, bool (*f)(void *, void *), void *e);
void		for_each(t_darray *s,
				void *(*f)(void *, t_gc *gc),
				void (*dest)(void *, t_gc *gc));
void		insert(t_darray *s, size_t i, void *e);
void		*peek(t_darray *s);
void		*peek_i(t_darray *s, size_t i);
void		*pop(t_darray *s);
void		*pop_i(t_darray *s, size_t i);
void		push(t_darray *s, void *e);
void		*reduce(t_darray *s,
				void *(*f)(void *, void *, t_gc *),
				void *acc,
				void (*dest)(void *, t_gc *));
void		repr(t_darray *s, void (*repr_item)(void *));
void		set(t_darray *s, size_t i, void *e, void (*dest)(void *, t_gc *));
void		sort(t_darray *s, bool (*f)(void *, void *));

t_darray	*new_darray(t_gc *gc)
{
	t_darray	*darray;

	darray = gc_malloc(sizeof(t_darray), gc);
	darray->arr = gc_calloc((DARRAY_LEN + 1), sizeof(void *), gc);
	darray->len = 0;
	darray->capacity = DARRAY_LEN;
	darray->gc = gc;
	darray->repr = repr;
	darray->peek_i = peek_i;
	darray->peek = peek;
	darray->insert = insert;
	darray->push = push;
	darray->pop_i = pop_i;
	darray->pop = pop;
	darray->sort = sort;
	darray->set = set;
	darray->any = any;
	darray->find = find;
	darray->find_i = find_i;
	darray->for_each = for_each;
	darray->filter = filter;
	darray->reduce = reduce;
	return (darray);
}

t_darray	*new_darray_from_arr(void **arr, t_gc *gc)
{
	t_darray	*darray;
	size_t		i;

	darray = new_darray(gc);
	i = 0;
	while (arr[i])
		darray->push(darray, arr[i++]);
	return (darray);
}

t_darray	*copy(t_darray *original, void *(*copy)(void *, t_gc *))
{
	t_darray	*new;
	size_t		i;

	new = new_darray(original->gc);
	i = 0;
	while (i < original->len)
	{
		if (copy)
			new->push(new, copy(original->arr[i], new->gc));
		else
			new->push(new, original->arr[i++]);
	}
	return (new);
}

void	dest_darray(t_darray *darray, void (*dest)(void *, t_gc *))
{
	size_t	i;

	i = 0;
	while (i < darray->len)
		dest(darray->arr[i++], darray->gc);
	gc_free(darray->arr, darray->gc);
	gc_free(darray, darray->gc);
}
