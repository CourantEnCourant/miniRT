/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 20:38:12 by weizhang          #+#    #+#             */
/*   Updated: 2025/11/22 01:25:12 by weiqizhang       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isupper(int a)
{
	return ('A' <= a && a <= 'Z');
}

static int	ft_islower(int a)
{
	return ('a' <= a && a <= 'z');
}

int	ft_isalpha(int a)
{
	return (ft_isupper(a) || ft_islower(a));
}
