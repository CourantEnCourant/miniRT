/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 16:38:34 by weizhang          #+#    #+#             */
/*   Updated: 2025/11/15 16:50:37 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*d;

	d = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (d == NULL)
		return (NULL);
	ft_strlcpy(d, s, sizeof(char) * ft_strlen(s) + 1);
	return (d);
}
