/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 16:56:16 by weizhang          #+#    #+#             */
/*   Updated: 2025/11/23 18:26:03 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "gc_libft.h"
#include "libft.h"

static size_t	ft_min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

char	*gc_substr(char const *s, unsigned int start, size_t len, t_gc *gc)
{
	char	*substr;
	size_t	substr_len;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (gc_calloc(1, sizeof(char), gc));
	substr_len = ft_min(ft_strlen(s + start), len);
	substr = gc_malloc(sizeof(char) * (substr_len + 1), gc);
	ft_strlcpy(substr, &s[start], substr_len + 1);
	return (substr);
}
