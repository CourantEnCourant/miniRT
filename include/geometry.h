/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 08:57:04 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/09 10:11:10 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H

# include "tuple.h"

enum e_rgb
{
	R,
	G,
	B,
};

typedef t_tuple				t_rgb;
t_rgb			color(double r, double g, double b);
t_rgb			color_add(t_rgb c1, t_rgb c2);
t_rgb			color_mult(t_rgb c1, t_rgb c2);
t_rgb			color_sub(t_rgb c1, t_rgb c2);
t_rgb			color_scal_mult(t_rgb c, double scale);
unsigned int	normalized_rgb_to_int(t_rgb rgb);
unsigned int	rgb_to_int(t_rgb rgb);

enum e_type
{
	SPHERE,
	PLANE,
	CYL,
};

typedef struct s_shape		t_shape;
struct s_shape
{
	enum e_type	type;
	t_tuple		coord;
	t_rgb		rgb;
	const char	*(*get_type)(const t_shape *self);
};
void			init_shape(t_shape *s, enum e_type t, t_tuple coord, t_rgb rgb);

typedef struct s_sphere		t_sphere;
struct s_sphere
{
	t_shape	base;
	double	radius;
};
void			init_sphere(t_sphere *s, t_tuple coord, t_rgb rgb, double rad);

typedef struct s_plane		t_plane;
struct s_plane
{
	t_shape	base;
	t_tuple	normal;
};
void			init_plane(t_plane *s, t_tuple coord, t_rgb rgb,
					t_tuple normal);

typedef struct s_cylinder	t_cyl;
struct s_cylinder
{
	t_shape	base;
	t_tuple	normal;
	double	radius;
	double	height;
};
void			init_cyl1(t_cyl *self, t_tuple coord, t_rgb rgb,
					t_tuple normal);
void			init_cyl2(t_cyl *self, double radius, double height);

#endif
