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

# include <stdbool.h>
# include "gc.h"

typedef struct s_darray	t_darray;
struct	s_darray
{
	void		**arr;
	size_t		len;
	size_t		capacity;
	t_gc		*gc;
	bool		(*any)(const t_darray *,
		bool (*)(const void *, const void *),
		const void *);
	t_darray	*(*filter)(const t_darray *,
			bool (*)(const void *, const void *),
			void *(*copy)(const void *org, t_gc *gc),
			const void *);
	const void	*(*find)(const t_darray *,
			bool (*)(const void *, const void *),
			const void *);
	size_t		(*find_i)(const t_darray *,
		bool (*f)(const void *, const void *),
		const void *);
	void		(*for_each)(t_darray *, void *(*f)(void *, t_gc *),
			void (*dest)(void *, t_gc *));
	void		(*insert)(t_darray *self, size_t i, const void *item);
	const void	*(*peek)(const t_darray *self);
	const void	*(*peek_i)(const t_darray *self, size_t i);
	void		*(*pop_i)(t_darray *self, size_t i);
	void		*(*pop)(t_darray *self);
	void		(*push)(t_darray *self, const void *item);
	void		*(*reduce)(const t_darray *,
			void *(*f)(const void *, const void *, t_gc *),
			void *,
			void (*dest)(void *, t_gc *));
	void		(*repr)(const t_darray *self,
			void (*repr_item)(const void *));
	void		(*sort)(t_darray *self, bool (*)(const void *, const void *));
	void		(*set)(t_darray *self,
			size_t i,
			const void *item,
			void (*dest)(void *, t_gc *));
};
t_darray	*new_darray(t_gc *gc);
t_darray	*new_darray_from_arr(const void **arr, t_gc *gc);
t_darray	*copy(const t_darray *original,
				void *(*copy)(const void *, t_gc *));
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
