#include <stdio.h>
#include <assert.h>
#include "minirt.h"
#include "tuple.h"

void	p69(void)
{
	t_ray ray = init_ray(point(1, 2, 3), vector(0, 1, 0));

	// Translating a ray
	t_ray r2 = transform(ray, mat_translate(3, 4, 5));
	t_ray expected = init_ray(point(4, 6, 8), vector(0, 1, 0));
	assert(ray_eq(r2, expected));

	// scaling a ray
	t_ray r3 = transform(ray, mat_scal(2, 3, 4));
	expected = init_ray(point(2, 6, 12), vector(0, 3, 0));
	assert(ray_eq(r3, expected));
}


int	main(void)
{
	p69();
	printf("All tests passed\n");
}
