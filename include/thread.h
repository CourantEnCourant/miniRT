/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 09:01:26 by weizhang          #+#    #+#             */
/*   Updated: 2026/11/07 09:35:21 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include <pthread.h>
# include <stddef.h>
# include "minirt.h"

typedef struct s_thread
{
	pthread_t	thread;
	size_t		i;
	size_t		thread_count;
	const t_renderer	*renderer;
	const t_conf		*conf;
}	t_thread;

void init_thread(t_thread *thread,
		size_t i,
		size_t thread_count,
		const t_renderer *renderer,
		const t_conf *conf);

#endif
