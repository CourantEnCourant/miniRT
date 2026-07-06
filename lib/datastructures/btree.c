/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 15:49:27 by weizhang          #+#    #+#             */
/*   Updated: 2026/03/17 15:50:23 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "datastructures.h"
#include "gc_libft.h"
#include "libft.h"
#include <unistd.h>

static void	repr_cld(t_btree *s, char *pre, bool left, void (*repr_v)(void *v))
{
	char	*new_prefix;

	if (!s)
		return ;
	ft_printf("%s", pre);
	if (left)
	{
		ft_printf("%s", "├── ");
		new_prefix = gc_strjoin(pre, "│   ", s->gc);
	}
	else
	{
		ft_printf("%s", "└── ");
		new_prefix = gc_strjoin(pre, "    ", s->gc);
	}
	repr_v(s->value);
	write(1, "\n", 1);
	repr_cld(s->left, new_prefix, true, repr_v);
	repr_cld(s->right, new_prefix, false, repr_v);
}

static void	repr(t_btree *s, void (*repr_v)(void *v))
{
	if (!s || !s->value)
		return ;
	repr_v(s->value);
	write(1, "\n", 1);
	repr_cld(s->left, "", true, repr_v);
	repr_cld(s->right, "", false, repr_v);
}

t_btree	*init_btree(void *value, t_gc *gc)
{
	t_btree	*btree;

	btree = gc_malloc(sizeof(t_btree), gc);
	btree->value = value;
	btree->left = NULL;
	btree->right = NULL;
	btree->gc = gc;
	btree->repr = repr;
	return (btree);
}
