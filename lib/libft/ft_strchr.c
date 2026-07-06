/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 18:44:06 by weiqi             #+#    #+#             */
/*   Updated: 2025/11/23 15:26:18 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = -1;
	while (s[++i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)s + i);
	}
	if ((unsigned char)c == '\0')
		return ((char *)s + i);
	return (NULL);
}
