/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 19:18:22 by weizhang          #+#    #+#             */
/*   Updated: 2026/02/07 02:21:45 by weiqizhang       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "gc_libft.h"
#include "libft.h"

static size_t	ft_strlen_sep(const char *s, char sep)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != sep)
		len++;
	return (len);
}

static char	*extract_line(char **stash, t_gc *gc)
{
	int		stash_len;
	char	*substring;
	int		substring_len;

	stash_len = ft_strlen(*stash);
	if (stash_len == 0)
		return (NULL);
	substring_len = ft_strlen_sep(*stash, '\n') + 1;
	substring = gc_substr(*stash, 0, substring_len, gc);
	*stash = gc_substr(*stash, substring_len, stash_len - substring_len, gc);
	return (substring);
}

char	*gc_get_next_line(int fd, t_gc *gc)
{
	static char	*stash[1024];
	int			read_result;
	char		*temp;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	if (-1024 < fd && fd < 0)
	{
		if (stash[-fd])
			stash[-fd] = NULL;
		return (NULL);
	}
	if (fd < 1024 && !stash[fd])
		stash[fd] = gc_calloc(1, sizeof(char), gc);
	while (!ft_strchr(stash[fd], '\n'))
	{
		temp = gc_calloc(BUFFER_SIZE + 1, sizeof(char), gc);
		read_result = read(fd, temp, BUFFER_SIZE);
		if (read_result == 0)
			break ;
		if (read_result == -1)
			return (NULL);
		stash[fd] = gc_strjoin(stash[fd], temp, gc);
	}
	return (extract_line(&stash[fd], gc));
}
