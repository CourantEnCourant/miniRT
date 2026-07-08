/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datastructures.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqizhang <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 12:58:22 by weiqizhang        #+#    #+#             */
/*   Updated: 2026/05/11 22:19:59 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATASTRUCTURES_H
# define DATASTRUCTURES_H

# define DARRAY_LEN 42

# include "gc_libft.h"
# include <stdbool.h>

typedef struct s_darray	t_darray;
struct	s_darray
{
	void		**arr;
	size_t		len;
	size_t		capacity;
	t_gc		*gc;
	void		(*repr)(t_darray *self, void (*repr_item)(void *value));
	void		*(*peek_i)(t_darray *self, size_t i);
	void		*(*peek)(t_darray *self);
	void		(*insert)(t_darray *self, size_t i, void *item);
	void		(*push)(t_darray *self, void *item);
	void		*(*pop_i)(t_darray *self, size_t i);
	void		*(*pop)(t_darray *self);
	void		(*sort)(t_darray *self, bool (*)(void *, void *));
	void		(*set)(t_darray *self,
			size_t i,
			void *item,
			void (*dest)(void *, t_gc *));
	bool		(*any)(t_darray *, bool (*)(void *, void *), void *);
	void		*(*find)(t_darray *, bool (*)(void *, void *), void *);
	size_t		(*find_i)(t_darray *, bool (*)(void *, void *), void *);
	void		(*for_each)(t_darray *, void *(*f)(void *, t_gc *),
			void (*dest)(void *, t_gc *));
	t_darray	*(*filter)(t_darray *, bool (*)(void *, void *), void *);
	void		*(*reduce)(t_darray *,
			void *(*)(void *, void *, t_gc *),
			void *,
			void (*dest)(void *, t_gc *));
};
t_darray	*new_darray(t_gc *gc);
t_darray	*new_darray_from_arr(void **arr, t_gc *gc);
t_darray	*copy(t_darray *original, void *(*copy)(void *, t_gc *));
void		dest_darray(t_darray *darray, void (*dest)(void *, t_gc *));

typedef struct s_btree	t_btree;
struct	s_btree
{
	void		*value;
	t_btree		*left;
	t_btree		*right;
	t_gc		*gc;
	void		(*repr)(t_btree *s, void (*repr_v)(void *v));
};
t_btree		*init_btree(void *value, t_gc *gc);

#endif
