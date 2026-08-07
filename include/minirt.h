/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 08:57:04 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/21 21:24:19 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIN_W 1920
# define WIN_H 1080
# define XS_SIZE 100
# ifdef __APPLE__
#  define KEY_ESC 53
# else
#  define KEY_ESC 65307
# endif
# define EVENT_DESTROY 17
# define MASK_DESTROY 0

# include "datastructures.h"
# include "gc_libft.h"
# include "tuple.h"

typedef int	(*t_fn)(void);

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
unsigned int	rgb_to_int(t_rgb rgb);

enum e_type
{
	CONE,
	CYL,
	PLANE,
	SPHERE,
};

typedef	struct	s_material
{
	t_rgb	rgb;
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
}	t_material;
t_material	default_material(void);

typedef struct s_ray	t_ray;
struct s_ray
{
	t_tuple	orig;
	t_tuple	dir;
};

typedef struct s_shape		t_shape;

typedef struct s_intersection
{
	double	t;
	t_shape	*shape;
}	t_intersection;

typedef struct s_xs
{
	unsigned int	count;
	t_intersection	xs[XS_SIZE];
}	t_xs;

struct s_shape
{
	enum e_type	type;
	t_tuple		coord;
	t_material	material;
	t_mat		transform;
	t_mat		transform_inv;
	t_mat		transform_inv_t;
	const char	*(*get_type)(const t_shape *self);
	void		(*intersect)(const t_shape *self, t_xs *xs, t_ray ray);
	t_tuple		(*local_normal_at)(const t_shape *self, t_tuple p);
};
void			init_shape(t_shape *s, enum e_type t, t_tuple coord, t_rgb rgb);
void			set_matrices(t_shape *self, t_mat transform);
t_tuple			world_normal_at(const t_shape *self, t_tuple p);

typedef struct s_sphere		t_sphere;
struct s_sphere
{
	t_shape	base;
	double	radius;
};
void			init_sphere(t_sphere *s, t_tuple coord, t_rgb rgb, double rad);
t_tuple			reflect(t_tuple in, t_tuple normal);

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
void			init_cyl(t_cyl *self, t_tuple coord, t_rgb rgb,
					t_tuple normal, double radius, double height);

typedef struct s_cone	t_cone;
struct s_cone
{
	t_shape	base;
	double	radius;
	double	height;
};
void			init_cone(t_cone *self, t_tuple coord, t_rgb rgb,
		t_tuple normal, double radius, double height);

typedef struct s_am		t_am;
struct s_am
{
	double	ratio;
	t_rgb	rgb;
	bool	(*is_valid)(const t_am * self);
};

typedef struct s_camera	t_camera;
struct s_camera
{
	t_tuple	coord;
	t_tuple	normal;
	double	hfov_rad;
	double	half_width;
	double	half_height;
	double	pixel_size;
	t_mat	transform;
	t_mat	transform_inv;
	bool	(*is_valid)(const t_camera * self);
};

typedef struct s_light	t_light;
struct s_light
{
	t_tuple	coord;
	double	brightness;
	t_rgb	rgb;
};
t_light	*new_light(t_tuple coord, double brightness, t_rgb rgb, t_gc *gc);

t_ray	init_ray(t_tuple orig, t_tuple dir);
t_tuple	ray_at(t_ray ray, double t);
bool	ray_eq(t_ray r1, t_ray r2);
t_ray	ray_for_pixel(const t_camera *cam, double px, double py);

typedef struct s_comps
{
	double	t;
	t_shape	*shape;
	t_tuple	p;
	t_tuple	over_point;
	t_tuple	eyev;
	t_tuple	normalv;
	bool	inside;
}	t_comps;
t_comps	prepare_computations(t_intersection inter, t_ray r);

typedef struct s_conf	t_conf;
struct s_conf
{
	t_am		am;
	t_camera	camera;
	t_darray	*lights;
	t_gc		*gc;
	t_darray	*shapes;
	void		(*repr)(const t_conf *self);
};
bool	init_conf_from_file(t_conf *self, int fd, t_gc *gc);
void	dest_conf(t_conf *self);
t_mat	view_transform(t_tuple from, t_tuple to, t_tuple up);

t_xs			intersect_world(t_ray ray, const t_conf *conf);
t_intersection	hit(const t_xs *xs);
t_ray			transform(t_ray ray, t_mat matrix);
t_rgb			shade_hit(const t_conf *conf, t_comps comps);

typedef struct s_rend	t_renderer;
struct s_rend
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_conf	*conf;
	t_gc	*gc;
	void	(*render)(const t_renderer *self, const t_conf *conf);
};
void	init_renderer(t_renderer *self, t_conf *conf, t_gc *gc,
			const char title[]);
void	dest_renderer(t_renderer *self);

#endif
