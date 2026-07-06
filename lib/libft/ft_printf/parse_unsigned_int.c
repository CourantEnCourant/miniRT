/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_unsigned_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqizhang <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 01:44:37 by weiqizhang        #+#    #+#             */
/*   Updated: 2025/12/01 17:49:02 by weiqi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	parse_unsigned_int(int fd, unsigned int n)
{
	int		count;

	count = 0;
	if (n < 10)
	{
		n += '0';
		write(fd, &n, 1);
		return (1);
	}
	count += parse_unsigned_int(fd, n / 10);
	count += parse_unsigned_int(fd, n % 10);
	return (count);
}
