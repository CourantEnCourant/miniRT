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

# define WIN_W 800
# define WIN_H 600
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
# include "geometry.h"
# include "tuple.h"

typedef int	(*t_fn)(void);

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

typedef struct s_ray	t_ray;
struct s_ray
{
	t_tuple	orig;
	t_tuple	dir;
};
t_ray	init_ray(t_tuple orig, t_tuple dir);
t_tuple	ray_at(t_ray ray, double t);
bool	ray_eq(t_ray r1, t_ray r2);

typedef struct s_intersection
{
	double	t;
	t_shape	*shape;
}	t_intersection;

typedef struct s_comps
{
	double	t;
	t_shape	*shape;
	t_tuple	p;
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

typedef struct s_xs
{
	unsigned int	count;
	t_intersection	xs[XS_SIZE];
}	t_xs;
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
void	init_renderer(t_renderer *self, t_conf *conf, t_gc *gc);
void	dest_renderer(t_renderer *self);

#endif
