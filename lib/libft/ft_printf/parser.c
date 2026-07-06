/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqizhang <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:41:28 by weiqizhang        #+#    #+#             */
/*   Updated: 2025/12/02 10:29:04 by weiqi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdbool.h>
#include "libft.h"

int	parse_char(int fd, char a);
int	parse_str(int fd, char *s);
int	parse_int(int fd, int n);
int	parse_pointer(int fd, void *ptr);
int	parse_unsigned_int(int fd, unsigned int n);
int	parse_unsigned_hex(int fd, unsigned int n, bool upper);

int	parse_arg(int fd, char arg, va_list args)
{
	if (arg == 'c')
		return (parse_char(fd, va_arg(args, int)));
	if (arg == 's')
		return (parse_str(fd, va_arg(args, char *)));
	if (arg == 'p')
		return (parse_pointer(fd, va_arg(args, void *)));
	if (arg == 'd' || arg == 'i')
		return (parse_int(fd, va_arg(args, int)));
	if (arg == 'u')
		return (parse_unsigned_int(fd, va_arg(args, unsigned int)));
	if (arg == 'x')
		return (parse_unsigned_hex(fd, va_arg(args, unsigned int), false));
	if (arg == 'X')
		return (parse_unsigned_hex(fd, va_arg(args, unsigned int), true));
	if (arg == '%')
	{
		ft_putchar_fd('%', fd);
		return (1);
	}
	return (-1);
}
