/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 08:57:04 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/24 06:48:20 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUPLE_H
# define TUPLE_H

# include <stdbool.h>
# include <stddef.h>
# define EPSILON 0.00001

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
t_tuple	tuple_hadamar(t_tuple t1, t_tuple t2);
double	tuple_mod(t_tuple t);
t_tuple	tuple_normalize(t_tuple t);
t_tuple	point(double x, double y, double z);
t_tuple	tuple_scal_div(t_tuple t, double scale);
t_tuple	tuple_scal_mult(t_tuple t, double scale);
t_tuple	tuple_sub(t_tuple t1, t_tuple t2);
t_tuple	vector(double x, double y, double z);

typedef struct s_mat
{
	double	arr[4][4];
	size_t	size;
}	t_mat;

// Matrix operations
double	mat_cofactor(t_mat A, size_t row, size_t col);
double	mat_det(t_mat A);
bool	mat_eq(t_mat A, t_mat B);
t_mat	mat_inv(t_mat A);
double	mat_minor(t_mat A, size_t row, size_t col);
t_mat	mat_mul(t_mat A, t_mat B);
t_tuple	mat_mul_tuple(t_mat A, t_tuple t);
t_mat	mat_subm(t_mat A, size_t row, size_t col);
t_mat	mat_scal_mult(t_mat A, double scale);
t_mat	mat_t(t_mat A);

// Matrix instances
t_mat	mat_id(void);
t_mat	mat_rotate_x(double radian);
t_mat	mat_rotate_y(double radian);
t_mat	mat_rotate_z(double radian);
t_mat	mat_scal(double x, double y, double z);
t_mat	mat_shear(double components[6]);
t_mat	mat_translate(double x, double y, double z);

// helpers
bool	deq(double a, double b);

#endif
