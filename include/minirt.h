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

typedef int				(*t_fn)(void);

enum e_rgb
{
	R,
	G,
	B,
};

typedef t_tuple			t_rgb;
t_rgb			color(double r, double g, double b);
t_rgb			color_add(t_rgb c1, t_rgb c2);
t_rgb			color_mult(t_rgb c1, t_rgb c2);
t_rgb			color_scal_mult(t_rgb c, double scale);
unsigned int	rgb_to_int(t_rgb rgb);

enum e_type
{
	CONE,
	CYL,
	PLANE,
	SPHERE,
};

typedef struct s_material
{
	t_rgb	rgb;
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
}	t_material;
t_material		default_material(void);

typedef struct s_ray
{
	t_tuple	orig;
	t_tuple	dir;
}	t_ray;

typedef struct s_shape	t_shape;

typedef struct s_intersection
{
	double	t;
	t_shape	*shape;
}	t_intersection;

typedef struct s_xs
{
	t_intersection	best;
}	t_xs;

struct s_shape
{
	enum e_type	type;
	t_tuple		coord;
	t_material	material;
	t_mat		transform;
	t_mat		transform_inv;
	t_mat		transform_inv_t;
	void		(*intersect)(const t_shape *self, t_xs *xs, t_ray ray);
	t_tuple		(*local_normal_at)(const t_shape * self, t_tuple p);
};
void			init_shape(t_shape *s, enum e_type t, t_tuple coord, t_rgb rgb);
void			set_matrices(t_shape *self, t_mat transform);
t_tuple			world_normal_at(const t_shape *self, t_tuple p);

typedef struct s_sphere
{
	t_shape	base;
}	t_sphere;
bool			add_sphere(t_darray *shapes, t_darray *param);
t_tuple			reflect(t_tuple in, t_tuple normal);

typedef struct s_plane
{
	t_shape	base;
}	t_plane;
bool			add_plane(t_darray *shapes, t_darray *param);

typedef struct s_cyl
{
	t_shape	base;
	double	height;
}	t_cyl;
void			init_cyl1(t_cyl *self, t_tuple coord, t_rgb rgb);
void			init_cyl2(t_cyl *self,
					t_tuple normal, double radius, double height);
bool			add_cyl(t_darray *shapes, t_darray *param);

typedef struct s_cone	t_cone;
struct s_cone
{
	t_shape	base;
	double	height;
};
void			init_cone1(t_cone *self, t_tuple coord, t_rgb rgb);
void			init_cone2(t_cone *self,
					t_tuple normal, double radius, double height);
bool			add_cone(t_darray *shapes, t_darray *param);

typedef struct s_am		t_am;
struct s_am
{
	double	ratio;
	t_rgb	rgb;
};
bool			init_am(t_am *am, t_darray *param);

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
};
bool			init_camera(t_camera *cam, t_darray *param);

typedef struct s_light	t_light;
struct s_light
{
	t_tuple	coord;
	double	brightness;
	t_rgb	rgb;
};
bool			add_light(t_darray *lights, t_darray *param);

t_tuple			ray_at(t_ray ray, double t);
t_ray			ray_for_pixel(const t_camera *cam, double px, double py);

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
t_comps			prepare_computations(t_intersection inter, t_ray r);

typedef struct s_conf	t_conf;
struct s_conf
{
	t_am		am;
	t_camera	camera;
	t_darray	*lights;
	t_gc		*gc;
	t_darray	*shapes;
};
bool			init_conf_from_file(t_conf *self, int fd, t_gc *gc);
void			dest_conf(t_conf *self);

void			add_xs(t_xs *xs, const t_shape *shape, double t);
void			intersect_world(t_xs *xs, t_ray ray, const t_conf *conf);
bool			shadow_hit(const t_conf *conf, t_ray ray, double distance);
t_ray			transform(t_ray ray, const t_mat *matrix);
t_rgb			ray_color(t_ray r, const t_conf *conf);
t_rgb			shade_hit(const t_conf *conf, t_comps comps);
t_rgb			lighting(const t_conf *conf, t_material material,
					const t_light *light, t_comps comps);

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
void			init_renderer(t_renderer *self, t_conf *conf, t_gc *gc,
					const char title[]);
void			render(const t_renderer *self, const t_conf *conf);

bool			parse_rgb(t_rgb *rgb, char str[], t_gc *gc);
bool			parse_coord(t_tuple *coord, char str[], t_gc *gc);
bool			parse_normal(t_tuple *normal, char str[], t_gc *gc);

#endif
