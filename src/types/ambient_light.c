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

bool	init_am(t_am *am, t_darray *param, t_conf *conf)
{
	if (conf->am_is_valid || param->len != 3)
		return (false);
	am->ratio = ft_atof(param->arr[1]);
	if (am->ratio < 0 || am->ratio > 1)
		return (false);
	if (!parse_rgb(&am->rgb, param->arr[2], param->gc))
		return (false);
	conf->am_is_valid = true;
	return (true);
}
