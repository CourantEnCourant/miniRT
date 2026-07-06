/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weiqizhang <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 01:20:39 by weiqizhang        #+#    #+#             */
/*   Updated: 2025/12/02 22:40:25 by weiqizhang       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	parse_int(int fd, int nbr)
{
	char	*nbr_str;
	int		nbr_len;

	nbr_str = ft_itoa(nbr);
	if (!nbr_str)
		return (-1);
	ft_putstr_fd(nbr_str, fd);
	nbr_len = ft_strlen(nbr_str);
	free(nbr_str);
	return (nbr_len);
}
