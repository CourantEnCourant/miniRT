/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 22:36:47 by weizhang          #+#    #+#             */
/*   Updated: 2026/04/16 22:37:28 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include "libft.h"

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, s);
	ret = ft_vdprintf(STDOUT_FILENO, s, ap);
	va_end(ap);
	return (ret);
}
