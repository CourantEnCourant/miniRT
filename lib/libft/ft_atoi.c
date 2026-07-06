/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:37:46 by weizhang          #+#    #+#             */
/*   Updated: 2026/05/10 17:53:59 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		result;
	int		is_neg;

	i = 0;
	result = 0;
	is_neg = -1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			is_neg *= -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		result = result * 10 - (nptr[i] - '0');
		i++;
	}
	return (is_neg * result);
}
