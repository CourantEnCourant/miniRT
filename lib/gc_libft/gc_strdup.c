/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anying <anying@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 19:24:25 by weizhang          #+#    #+#             */
/*   Updated: 2026/03/26 15:14:30 by anying           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "gc_libft.h"
#include "libft.h"

char	*gc_strdup(char *s, t_gc *gc)
{
	char	*s_dup;

	s_dup = ft_strdup(s);
	if (!s_dup)
	{
		gc->clean(gc);
		exit(EXIT_FAILURE);
	}
	gc->add(gc, s_dup);
	return (s_dup);
}
