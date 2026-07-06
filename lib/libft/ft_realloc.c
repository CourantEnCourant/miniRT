/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 19:12:52 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/06 19:46:48 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

static size_t	ft_min(size_t num1, size_t num2)
{
	if (num1 < num2)
		return (num1);
	return (num2);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t size)
{
	void	*new_ptr;

	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	if (!ptr)
		return (new_ptr);
	ft_memcpy(new_ptr, ptr, ft_min(old_size, size));
	free(ptr);
	return (new_ptr);
}
