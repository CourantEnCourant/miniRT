/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 09:05:00 by weizhang          #+#    #+#             */
/*   Updated: 2026/11/07 09:35:02 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"

#include <stddef.h>
#include "minirt.h"

void init_thread(t_thread *self,
		size_t i,
		size_t thread_count,
		const t_renderer *renderer,
		const t_conf *conf)
{
	self->i = i;
	self->thread_count = thread_count;
	self->renderer = renderer;
	self->conf = conf;
}
