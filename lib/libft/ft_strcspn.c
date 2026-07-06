/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 23:17:03 by weizhang          #+#    #+#             */
/*   Updated: 2026/05/11 23:18:39 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strcspn(char *s, char *reject)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (ft_strchr(reject, s[i]))
			return (i);
		i++;
	}
	return (i);
}
