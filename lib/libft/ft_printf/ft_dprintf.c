/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 22:26:02 by weizhang          #+#    #+#             */
/*   Updated: 2026/04/16 22:27:34 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

int	ft_dprintf(int fd, const char *s, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, s);
	ret = ft_vdprintf(fd, s, ap);
	va_end(ap);
	return (ret);
}
