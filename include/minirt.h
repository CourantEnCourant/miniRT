/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 08:57:04 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/13 22:24:26 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIN_W 800
# define WIN_H 600

# include "datastructures.h"
# include "gc_libft.h"
# include "geometry.h"
# include "vector.h"

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
	t_vec3	coord;
	t_vec3	normal;
	double	fov;
	bool	(*is_valid)(const t_camera * self);
};

typedef struct s_light	t_light;
struct s_light
{
	t_vec3	coord;
	double	brightness;
	t_rgb	rgb;
	bool	(*is_valid)(const t_light * self);
};

typedef struct s_conf	t_conf;
struct s_conf
{
	t_am		am;
	t_camera	camera;
	t_light		light;
	t_gc		*gc;
	t_darray	*shapes;
	void		(*repr)(const t_conf *self);
};
bool	init_conf_from_file(t_conf *self, int fd, t_gc *gc);
void	dest_conf(t_conf *self);

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
	t_gc	*gc;
	void	(*render)(const t_renderer *self);
};
void	init_renderer(t_renderer *self, t_gc *gc);
void	dest_renderer(t_renderer *self);

#endif
