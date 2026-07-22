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

static long long	ft_pow10(long long exponent)
{
	long long	res;

	res = 1;
	while (exponent-- > 0)
		res *= 10;
	return (res);
}

static void	parse_space_sign(const char **str, int *sign)
{
	while (ft_isspace(**str))
		(*str)++;
	*sign = 1;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			*sign = -1;
		(*str)++;
	}
}

double	ft_atof(const char str[])
{
	int			sign;
	long long	whole;
	long long	fract;
	long long	fract_size;

	parse_space_sign(&str, &sign);
	whole = 0;
	while (ft_isdigit(*str))
	{
		whole = whole * 10 + (*str - '0');
		str++;
	}
	fract = 0;
	fract_size = 0;
	if (*str == '.')
		str++;
	while (ft_isdigit(*str))
	{
		fract = fract * 10 + (*str - '0');
		fract_size++;
		str++;
	}
	return (sign * (whole + (double)fract / ft_pow10(fract_size)));
}
