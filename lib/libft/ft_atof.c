/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:37:46 by weizhang          #+#    #+#             */
/*   Updated: 2026/05/10 17:53:59 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

static long long	pow10(long long size)
{
	long long	res;

	res = 1;
	while (size-- > 0)
		res *= 10;
	return (res);
}

static const char	*parse_space_sign(const char *str, int *sign)
{
	while (ft_isspace(*str))
		str++;
	*sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			*sign = -1;
		str++;
	}
	return (str);
}

double	ft_atof(const char str[])
{
	int			sign;
	long long	size;
	long long	whole;
	long long	fract;

	str = parse_space_sign(str, &sign);
	whole = 0;
	while (ft_isdigit(*str))
	{
		whole = whole * 10 + (*str - '0');
		str++;
	}
	fract = 0;
	size = 0;
	if (*str == '.')
		str++;
	while (ft_isdigit(*str))
	{
		fract = fract * 10 + (*str - '0');
		size++;
		str++;
	}
	return (sign * (whole + (double)fract / pow10(size)));
}
