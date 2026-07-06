/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 13:47:39 by weiqi             #+#    #+#             */
/*   Updated: 2025/11/23 18:22:10 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*mapped;

	i = ft_strlen(s);
	mapped = malloc(sizeof(char) * (i + 1));
	if (!mapped)
		return (NULL);
	mapped[i] = '\0';
	while (i--)
		mapped[i] = f(i, s[i]);
	return (mapped);
}
