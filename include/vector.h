/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 08:57:04 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/10 01:48:00 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

enum e_component
{
	X,
	Y,
	Z,
};

typedef struct s_vec3
{
	double	arr[3];
}	t_vec3;

t_vec3	cross_product(t_vec3 v1, t_vec3 v2);
double	dot_product(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_add(t_vec3 v1, t_vec3 v2);
double	vec3_mod(t_vec3 v);
t_vec3	vec3_normalize(t_vec3 v);
t_vec3	vec3_scal_mult(t_vec3 v1, double scale);
t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_scal_div(t_vec3 v1, double scale);

#endif
