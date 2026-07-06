/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 19:18:22 by weizhang          #+#    #+#             */
/*   Updated: 2026/02/06 13:39:16 by weiqizhang       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

static bool	str_append_str(char *s1[], char s2[], size_t size1, size_t size2)
{
	char	*tmp;

	tmp = ft_realloc(*s1,
			size1 * sizeof(char),
			(size1 + size2 + 1) * sizeof(char));
	if (!tmp)
		return (false);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = '\0';
	*s1 = tmp;
	return (true);
}

static int	read_until_nl(int fd, char buf[], char **ret, size_t *ret_len)
{
	int	read_ret;

	while (!ft_strchr(buf, '\n'))
	{
		if (!str_append_str(ret, buf, *ret_len, ft_strlen(buf)))
			return (-1);
		*ret_len += ft_strlen(buf);
		buf[0] = '\0';
		read_ret = read(fd, buf, BUFFER_SIZE);
		if (read_ret == -1)
			return (-1);
		if (read_ret == 0)
			return (0);
		buf[read_ret] = '\0';
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*ret;
	size_t		ret_len;
	char		*ptr_newline;
	int			status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ret = NULL;
	ret_len = 0;
	status = read_until_nl(fd, buf, &ret, &ret_len);
	if (status == -1)
		return (free(ret), NULL);
	if (status == 0)
	{
		if (ret && ret[0])
			return (ret);
		return (free(ret), NULL);
	}
	ptr_newline = ft_strchr(buf, '\n');
	if (!str_append_str(&ret, buf, ret_len, ptr_newline - buf + 1))
		return (free(ret), NULL);
	ft_memmove(buf, ptr_newline + 1, ft_strlen(ptr_newline + 1) + 1);
	return (ret);
}
