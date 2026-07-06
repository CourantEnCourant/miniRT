/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:25:38 by weiqi             #+#    #+#             */
/*   Updated: 2025/11/22 01:58:21 by weiqizhang       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*s1;
	unsigned char		uc;

	s1 = s;
	uc = (unsigned char)c;
	i = -1;
	while (++i < n)
	{
		if (s1[i] == uc)
			return ((void *)s1 + i);
	}
	return (NULL);
}
