/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 08:57:04 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/23 00:00:00 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUPLE_H
# define TUPLE_H

/*
** A tuple is a 4-component double: (x, y, z, w).
** w == 0 makes it a vector (a direction), w == 1 makes it a point.
*/

enum e_component
{
	X,
	Y,
	Z,
	W,
};

typedef struct s_tuple
{
	double	arr[4];
}	t_tuple;

t_tuple	cross_product(t_tuple t1, t_tuple t2);
t_tuple	tuple_add(t_tuple t1, t_tuple t2);
double	tuple_dot(t_tuple t1, t_tuple t2);
double	tuple_mod(t_tuple t);
t_tuple	tuple_normalize(t_tuple t);
t_tuple	point(double x, double y, double z);
t_tuple	tuple_scal_div(t_tuple t, double scale);
t_tuple	tuple_scal_mult(t_tuple t, double scale);
t_tuple	tuple_sub(t_tuple t1, t_tuple t2);
t_tuple	vector(double x, double y, double z);

#endif
