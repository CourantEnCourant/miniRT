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
#include "gc.h"
#include "gc_libft.h"
#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	size_t	i;
	bool	in_word;
	int		wordcount;

	i = -1;
	in_word = false;
	wordcount = 0;
	while (s[++i])
	{
		if (!in_word && s[i] != c)
		{
			wordcount++;
			in_word = true;
		}
		else if (s[i] == c)
			in_word = false;
	}
	return (wordcount);
}

static int	ft_strlen_sep(char const *s, char sep)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != sep)
		i++;
	return (i);
}

char	**gc_split(char const *s, char c, t_gc *gc)
{
	size_t	j;
	bool	in_word;
	char	**strs;

	if (!s)
		return (NULL);
	strs = gc_malloc(sizeof(char *) * (ft_count_words(s, c) + 1), gc);
	j = -1;
	in_word = false;
	while (*s)
	{
		if (!in_word && *s != c)
		{
			in_word = true;
			strs[++j] = gc_malloc(sizeof(char) * (ft_strlen_sep(s, c) + 1), gc);
			ft_strlcpy(strs[j], s, ft_strlen_sep(s, c) + 1);
		}
		else if (*s == c)
			in_word = false;
		s++;
	}
	strs[++j] = NULL;
	return (strs);
}
