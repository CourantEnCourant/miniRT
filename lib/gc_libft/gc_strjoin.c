/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqizhang <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:03:04 by weiqizhang        #+#    #+#             */
/*   Updated: 2026/02/09 17:03:12 by weiqizhang       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "gc_libft.h"
#include "libft.h"

char	*gc_strjoin(char const *s1, char const *s2, t_gc *gc)
{
	char	*new;
	size_t	s1_len;
	size_t	s2_len;
	size_t	new_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_len = s1_len + s2_len;
	new = gc_malloc(sizeof(char) * (new_len + 1), gc);
	ft_strlcpy(new, s1, s1_len + 1);
	ft_strlcat(new, s2, new_len + 1);
	return (new);
}
