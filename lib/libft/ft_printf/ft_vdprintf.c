/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 18:19:52 by weiqi             #+#    #+#             */
/*   Updated: 2026/02/06 13:39:05 by weiqizhang       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdarg.h>
#include "libft.h"

int	parse_arg(int fd, char placeholder, va_list ap);

int	ft_vdprintf(int fd, const char *s, va_list ap)
{
	size_t	i;
	int		count;
	int		substr_count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			substr_count = parse_arg(fd, s[i + 1], ap);
			if (substr_count < 0)
				return (-1);
			count += substr_count;
			i += 2;
			continue ;
		}
		ft_putchar_fd(s[i], fd);
		i++;
		count++;
	}
	return (count);
}
