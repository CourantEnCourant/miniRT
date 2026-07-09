/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_libft.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anying <anying@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 20:31:24 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/07 06:39:23 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_LIBFT_H
# define GC_LIBFT_H

# include <stddef.h>
# include "datastructures.h"
# include "gc.h"

char		*gc_get_next_line(int fd, t_gc *gc);
char		*gc_itoa(int n, t_gc *gc);
t_darray	*gc_split(char const *s, char c, t_gc *gc);
char		*gc_strdup(char *s, t_gc *gc);
char		*gc_strjoin(char const *s1, char const *s2, t_gc *gc);
char		*gc_strtrim(char const *s1, char const *set, t_gc *gc);
char		*gc_substr(char const *s, unsigned int start, size_t len, t_gc *gc);

#endif
