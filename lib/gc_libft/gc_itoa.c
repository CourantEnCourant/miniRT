/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anying <anying@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:39:55 by anying            #+#    #+#             */
/*   Updated: 2026/03/26 15:31:17 by anying           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "gc_libft.h"

char	*gc_itoa(int n, t_gc *gc)
{
	char			*str;

	str = ft_itoa(n);
	if (!str)
	{
		gc->clean(gc);
		exit(EXIT_FAILURE);
	}
	gc->add(gc, str);
	return (str);
}
