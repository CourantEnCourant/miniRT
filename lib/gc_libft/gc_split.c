/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqizhang <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 22:27:01 by weiqizhang        #+#    #+#             */
/*   Updated: 2025/11/23 17:13:11 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include "datastructures.h"
#include "gc.h"
#include "gc_libft.h"

static int	ft_strlen_sep(char const *s, char sep)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != sep)
		i++;
	return (i);
}

t_darray	*gc_split(char const *s, char c, t_gc *gc)
{
	size_t		i;
	bool		in_word;
	t_darray	*words;

	if (!s)
		return (NULL);
	words = new_darray(gc);
	i = 0;
	in_word = false;
	while (s[i])
	{
		if (!in_word && s[i] != c)
		{
			in_word = true;
			words->push(words, gc_substr(s, i, ft_strlen_sep(&s[i], c), gc));
		}
		else if (s[i] == c)
			in_word = false;
		i++;
	}
	return (words);
}
