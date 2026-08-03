/*header to add*/


#include <math.h>
#include "minirt.h"
#include "tuple.h"

static const char	*get_type(const t_shape *self)
{
	(void)self;
	return ("cone");
}

static void	cap_intersect(const t_cone *cone, t_xs *xs, t_ray ray)
{
	double	cap_y;
	double	t;
	double	x;
	double	z;
 
	if (fabs(ray.dir.arr[Y]) < 1e-8)
		return ;
	cap_y = cone->base.coord.arr[Y] + cone->height;
	t = (cap_y - ray.orig.arr[Y]) / ray.dir.arr[Y];
	x = ray.orig.arr[X] + t * ray.dir.arr[X] - cone->base.coord.arr[X];
	z = ray.orig.arr[Z] + t * ray.dir.arr[Z] - cone->base.coord.arr[Z];
	if (x * x + z * z <= cone->radius * cone->radius)
	{
		xs->xs[xs->count].t = t;
		xs->xs[xs->count++].shape = (t_shape *)cone;
	}
}

static void	add_if_in_range(const t_cone *cone, t_xs *xs, t_tuple oc,
		t_ray ray, double t)
{
	double  y;
 
	y = oc.arr[Y] + t * ray.dir.arr[Y];
	if (y >= 0 && y <= cone->height)
	{
		xs->xs[xs->count].t = t;
		xs->xs[xs->count++].shape = (t_shape *)cone;
	}
}

static void	side_intersect(const t_cone *cone, t_xs *xs, t_ray ray)
{
	t_tuple	oc;
	double	k;
	double	a;
	double	b;
	double	c;
	double	disc;
 
	oc = tuple_sub(ray.orig, cone->base.coord);
	k = cone->radius / cone->height;
	a = ray.dir.arr[X] * ray.dir.arr[X] + ray.dir.arr[Z] * ray.dir.arr[Z]
		- k * k * ray.dir.arr[Y] * ray.dir.arr[Y];
	b = 2 * (oc.arr[X] * ray.dir.arr[X] + oc.arr[Z] * ray.dir.arr[Z]
		- k * k * oc.arr[Y] * ray.dir.arr[Y]);
	c = oc.arr[X] * oc.arr[X] + oc.arr[Z] * oc.arr[Z]
		- k * k * oc.arr[Y] * oc.arr[Y];
	if (fabs(a) < 1e-8)
	{
		if (fabs(b) > 1e-8)
			add_if_in_range(cone, xs, oc, ray, -c / b);
		return ;
	}
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return ;
	add_if_in_range(cone, xs, oc, ray, (-b - sqrt(disc)) / (2 * a));
	add_if_in_range(cone, xs, oc, ray, (-b + sqrt(disc)) / (2 * a));
}

static void	intersect(const t_shape *self, t_xs *xs, t_ray ray)
{
	const t_cone	*cone;
 
	cone = (const t_cone *)self;
	side_intersect(cone, xs, ray);
	cap_intersect(cone, xs, ray);
}

static t_tuple	normal_at(const t_shape *self, t_tuple p)
{
	const t_cone	*cone;
	t_tuple	local;
	double	k2;
 
	cone = (const t_cone *)self;
	local = tuple_sub(p, self->coord);
	k2 = (cone->radius / cone->height) * (cone->radius / cone->height);
	return (quadric_normal_at(local, 0, cone->height, false,
		2 * k2 * local.arr[Y]));

}

void	init_cone(t_cone *self, t_tuple coord, t_rgb rgb, double radius,
		double height)
{
	init_shape(&self->base, CONE, coord, rgb);
	self->radius = radius;
	self->height = height;
	self->base.get_type = get_type;
	self->base.intersect = intersect;
	self->base.normal_at = normal_at;
}
