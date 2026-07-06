/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:54:40 by weiqi             #+#    #+#             */
/*   Updated: 2025/11/22 03:13:49 by weiqizhang       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_intlen(int n)
{
	int	len;

	if (n <= 0)
		len = 1;
	else
		len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*ft_itoa(int n)
{
	size_t	i;
	char	*num_str;

	i = ft_intlen(n);
	num_str = malloc(sizeof(char) * (i + 1));
	if (num_str == NULL)
		return (NULL);
	num_str[i--] = '\0';
	if (n == 0)
	{
		num_str[0] = '0';
		return (num_str);
	}
	if (n < 0)
		num_str[0] = '-';
	while (n != 0)
	{
		num_str[i--] = ft_abs(n % 10) + '0';
		n /= 10;
	}
	return (num_str);
}
