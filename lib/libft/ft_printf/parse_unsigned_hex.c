/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_unsigned_hex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:57:34 by weiqi             #+#    #+#             */
/*   Updated: 2025/12/02 10:29:42 by weiqi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include "libft.h"

static int	ft_intlen_base(unsigned int n, unsigned int base)
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

static void	str_to_upper(char *s)
{
	size_t	i;

	i = -1;
	while (s[++i])
		s[i] = ft_toupper(s[i]);
	return ;
}

static char	*itohexa(unsigned int n, bool upper)
{
	char	*hexa;
	int		len;
	char	table[17];

	ft_strlcpy(table, "0123456789abcdef", 17);
	if (upper)
		str_to_upper(table);
	len = ft_intlen_base(n, 16);
	hexa = malloc(sizeof(char) * len + 1);
	if (!hexa)
		return (NULL);
	hexa[len--] = '\0';
	while (n / 16)
	{
		hexa[len--] = table[n % 16];
		n /= 16;
	}
	hexa[len] = table[n % 16];
	return (hexa);
}

int	parse_unsigned_hex(int fd, unsigned int n, bool upper)
{
	char	*hexa;
	int		len;

	hexa = itohexa(n, upper);
	len = ft_strlen(hexa);
	ft_putstr_fd(hexa, fd);
	free(hexa);
	return (len);
}
