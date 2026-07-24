/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 06:33:38 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/24 06:34:53 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "tuple.h"

bool	deq(double a, double b)
{
	return (fabs(a - b) < EPSILON);
}
