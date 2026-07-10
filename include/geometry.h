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

# include "vector.h"

typedef struct s_rgb		t_rgb;
struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
};

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
	t_vec3		coord;
	t_rgb		rgb;
	const char	*(*get_type)(const t_shape *self);
};
void	init_shape(t_shape *self, enum e_type type, t_vec3 coord, t_rgb rgb);

typedef struct s_sphere		t_sphere;
struct s_sphere
{
	t_shape	base;
	double	radius;
};
void	init_sphere(t_sphere *self, t_vec3 coord, t_rgb rgb, double radius);

typedef struct s_plane		t_plane;
struct s_plane
{
	t_shape	base;
	t_vec3	normal;
};
void	init_plane(t_plane *self, t_vec3 coord, t_rgb rgb, t_vec3 normal);

typedef struct s_cylinder	t_cyl;
struct s_cylinder
{
	t_shape	base;
	t_vec3	normal;
	double	radius;
	double	height;
};
void	init_cyl1(t_cyl *self, t_vec3 coord, t_rgb rgb, t_vec3 normal);
void	init_cyl2(t_cyl *self, double radius, double height);

#endif
