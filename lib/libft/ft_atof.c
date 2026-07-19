/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 23:10:51 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/18 21:14:19 by xiahuang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	parse_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

static double	parse_exponent(const char **str)
{
	int		exp_sign;
	int		exp_val;
	double	multiplier;

	if (**str != 'e' && **str != 'E')
		return (1.0);
	(*str)++;
	exp_val = 0;
	multiplier = 1.0;
	exp_sign = parse_sign(str);
	while (ft_isdigit(**str))
		exp_val = exp_val * 10 + (*(*str)++ - '0');
	while (exp_val-- > 0)
	{
		if (exp_sign == 1)
			multiplier *= 10.0;
		else
			multiplier /= 10.0;
	}
	return (multiplier);
}

double	ft_atof(const char *str)
{
	long long	res;
	long long	factor;
	int			sign;

	res = 0;
	factor = 1;
	while (ft_isspace(*str))
		str++;
	sign = parse_sign(&str);
	while (ft_isdigit(*str))
		res = res * 10 + (*str++ - '0');
	if (*str == '.')
		str++;
	while (ft_isdigit(*str))
	{
		res = res * 10 + (*str++ - '0');
		factor *= 10;
	}
	return (((double)res / factor * sign) * parse_exponent(&str));
}
