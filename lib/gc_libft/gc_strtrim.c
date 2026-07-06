/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 22:20:58 by weizhang          #+#    #+#             */
/*   Updated: 2026/03/15 22:24:03 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "gc_libft.h"

char	*gc_strtrim(char const *s1, char const *set, t_gc *gc)
{
	char	*trimmed;

	trimmed = ft_strtrim(s1, set);
	if (!trimmed)
	{
		gc->clean(gc);
		exit(EXIT_FAILURE);
	}
	gc->add(gc, trimmed);
	return (trimmed);
}
