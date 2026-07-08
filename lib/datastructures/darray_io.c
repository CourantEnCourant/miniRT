/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_io.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqizhang <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 21:31:04 by weiqizhang        #+#    #+#             */
/*   Updated: 2026/05/11 22:47:51 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "datastructures.h"
#include "gc_libft.h"
#include "libft.h"

void	insert(t_darray *s, size_t i, const void *item)
{
	void	**arr_ext;

	if (i > s->len)
	{
		ft_dprintf(STDERR_FILENO,
			"IndexError: max len is %d, insert at %d\n", s->len, i);
		return ;
	}
	if (s->len >= s->capacity)
	{
		s->capacity *= 2;
		arr_ext = gc_calloc(s->capacity + 1, sizeof(void *), s->gc);
		ft_memmove(arr_ext, s->arr, s->len * sizeof(void *));
		gc_free(s->arr, s->gc);
		s->arr = arr_ext;
	}
	ft_memmove(&s->arr[i + 1], &s->arr[i], (s->len - i) * sizeof(void *));
	s->arr[i] = (void *)item;
	s->len++;
}

void	push(t_darray *self, const void *item)
{
	self->insert(self, self->len, item);
}

void	*pop_i(t_darray *s, size_t i)
{
	void	*item;

	if (s->len == 0)
	{
		ft_dprintf(STDERR_FILENO,
			"IndexError: popped from empty darray\n");
		return (NULL);
	}
	if (i > s->len - 1)
	{
		ft_dprintf(STDERR_FILENO,
			"IndexError: max index %d, popped at %d\n", s->len - 1, i);
		return (NULL);
	}
	item = s->arr[i];
	ft_memmove(&s->arr[i], &s->arr[i + 1], (s->len - i) * sizeof(void *));
	s->len--;
	return (item);
}

void	*pop(t_darray *self)
{
	if (self->len == 0)
	{
		ft_dprintf(STDERR_FILENO,
			"IndexError: popped from empty darray\n");
		return (NULL);
	}
	return (self->pop_i(self, self->len - 1));
}

void	sort(t_darray *self, bool (*f)(const void *s1, const void *s2))
{
	size_t	i;
	size_t	j;
	void	*tmp;
	bool	is_sorted;

	i = 0;
	while (i < self->len)
	{
		is_sorted = true;
		j = 0;
		while (j < self->len - i - 1)
		{
			if (!f(self->arr[j], self->arr[j + 1]))
			{
				tmp = self->arr[j];
				self->arr[j] = self->arr[j + 1];
				self->arr[j + 1] = tmp;
				is_sorted = false;
			}
			j++;
		}
		if (is_sorted)
			break ;
		i++;
	}
}
