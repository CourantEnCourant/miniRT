/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 23:14:10 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/11 23:25:04 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "datastructures.h"
#include "libft.h"
#include "minirt.h"

static bool	is_valid(const t_am *self)
{
	return (0.0 <= self->ratio && self->ratio <= 1.0);
}

bool	init_am(t_am *am, t_darray *param)
{
	if (param->len != 3)
		return (false);
	am->ratio = ft_atof(param->arr[1]);
	if (!parse_rgb(&am->rgb, param->arr[2], param->gc))
		return (false);
	return (is_valid(am));
}
