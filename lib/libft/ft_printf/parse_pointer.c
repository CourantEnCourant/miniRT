/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqizhang <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 13:32:33 by weiqizhang        #+#    #+#             */
/*   Updated: 2025/12/02 22:40:18 by weiqizhang       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	parse_str(int fd, char *s);

static int	ft_numlen_base(unsigned long n, int base)
{
	int	len;

	if (n == 0)
		len = 1;
	else
		len = 0;
	while (n)
	{
		n /= base;
		len++;
	}
	return (len);
}

static char	*ptr_to_hex(unsigned long n)
{
	size_t	i;
	char	*num_str;
	char	table[17];

	ft_strlcpy(table, "0123456789abcdef", 17);
	i = ft_numlen_base(n, 16) + 2;
	num_str = malloc(sizeof(char) * i + 1);
	if (!num_str)
		return (NULL);
	ft_strlcpy(num_str, "0x", 3);
	num_str[i--] = '\0';
	while (n != 0)
	{
		num_str[i--] = table[n % 16];
		n /= 16;
	}
	return (num_str);
}

int	parse_pointer(int fd, void *ptr)
{
	unsigned long	ptr_value;
	char			*ptr_hex_str;
	size_t			ptr_hex_str_len;

	if (!ptr)
		return (parse_str(fd, "(nil)"));
	ptr_value = (unsigned long)ptr;
	ptr_hex_str = ptr_to_hex(ptr_value);
	if (!ptr_hex_str)
		return (-1);
	ft_putstr_fd(ptr_hex_str, fd);
	ptr_hex_str_len = ft_strlen(ptr_hex_str);
	free(ptr_hex_str);
	return (ptr_hex_str_len);
}
