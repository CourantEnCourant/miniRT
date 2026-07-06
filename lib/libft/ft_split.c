/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqizhang <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 22:27:01 by weiqizhang        #+#    #+#             */
/*   Updated: 2025/11/23 17:13:11 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
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

static char	**free_strs(char **strs, size_t j)
{
	size_t	i;

	i = -1;
	while (++i < j)
		free(strs[i]);
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	j;
	bool	in_word;
	char	**strs;

	strs = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!strs)
		return (NULL);
	j = -1;
	in_word = false;
	while (*s)
	{
		if (!in_word && *s != c)
		{
			in_word = true;
			strs[++j] = malloc(sizeof(char) * (ft_strlen_sep(s, c) + 1));
			if (!strs[j])
				return (free_strs(strs, j));
			ft_strlcpy(strs[j], s, ft_strlen_sep(s, c) + 1);
		}
		else if (*s == c)
			in_word = false;
		s++;
	}
	strs[++j] = NULL;
	return (strs);
}
