/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weizhang <weiqi.zhang_arthur@yahoo.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 08:57:04 by weizhang          #+#    #+#             */
/*   Updated: 2026/07/09 11:10:08 by weizhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "datastructures.h"
# include "gc_libft.h"
# include "geometry.h"
# include "vector.h"

typedef struct s_am
{
	double	ratio;
	t_rgb	rgb;
}	t_am;

typedef struct s_camera
{
	t_vec3	coord;
	t_vec3	normal;
	double	fov;
}	t_camera;

typedef struct s_light
{
	t_vec3	coord;
	double	brightness;
	t_rgb	rgb;
}	t_light;

typedef struct s_conf
{
	t_am		am;
	t_camera	camera;
	t_light		light;
	t_gc		*gc;
	t_darray	*shapes;
}	t_conf;
bool	init_conf_from_file(t_conf *self, int fd, t_gc *gc);
void	dest_conf(t_conf *self);

#endif
