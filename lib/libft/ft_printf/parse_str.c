/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqizhang <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 01:20:39 by weiqizhang        #+#    #+#             */
/*   Updated: 2025/12/02 22:40:01 by weiqizhang       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	parse_str(int fd, char *s)
{
	if (!s)
	{
		ft_putstr_fd("(null)", fd);
		return (ft_strlen("(null)"));
	}
	ft_putstr_fd(s, fd);
	return (ft_strlen(s));
}
