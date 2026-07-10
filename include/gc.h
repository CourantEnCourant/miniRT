/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anying <anying@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 20:31:24 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/07 06:39:23 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include <stddef.h>

typedef struct s_dllist	t_dllist;
struct	s_dllist
{
	void		*content;
	t_dllist	*next;
	t_dllist	*prev;
};
t_dllist	*new_dllist(void *content);
void		dllist_add_front(t_dllist **lst, t_dllist *node);
t_dllist	*find_dllist(t_dllist *self, void *content);
void		del_dllist(t_dllist *self, void (*del)(void *));
void		clear_dllist(t_dllist *self, void (*del)(void *));

typedef struct s_gc		t_gc;
struct	s_gc
{
	t_dllist	*start;
	void		(*add)(t_gc *self, void *item);
	void		(*del)(t_gc *self, void *item, void (*del_item)(void *));
};
t_gc		*new_gc(void);
void		dest_gc(t_gc *gc);

void		*gc_calloc(size_t nmemb, size_t size, t_gc *gc);
void		gc_free(void *ptr, t_gc *gc);
void		*gc_malloc(size_t size, t_gc *gc);

#endif
