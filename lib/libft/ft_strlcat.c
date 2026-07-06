/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:19:18 by weiqi             #+#    #+#             */
/*   Updated: 2025/11/16 00:11:04 by weiqizhang       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t dsize)
{
	size_t	i;
	size_t	j;
	size_t	concat_str_size;

	concat_str_size = ft_strlen(dst) + ft_strlen(src);
	if (dsize <= ft_strlen(dst))
		return (dsize + ft_strlen(src));
	i = 0;
	j = 0;
	while (dst[i])
		i++;
	while (i < dsize - 1 && src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (concat_str_size);
}
