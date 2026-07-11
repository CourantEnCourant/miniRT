/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 23:14:10 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/11 23:19:05 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "minirt.h"

bool	light_is_valid(const t_light *self)
{
	return (0.0 <= self->brightness && self->brightness <= 1.0);
}
