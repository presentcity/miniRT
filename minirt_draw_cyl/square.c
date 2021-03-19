#include "minirt.h"

double 	make_square(t_square *square, t_camera *cam) {
	double denom;
	t_vec3f hit_point;
	t_vec3f p0l0;
	double t;

	denom = dotproduct(square->n, cam->dir);
	if ( denom < 1e-6 ) {
		p0l0 = vec_dif(square->p0, cam->loc);
		t = dotproduct(p0l0, square->n) / denom;
		hit_point = vec_summary(cam->loc, mult(cam->dir, t));
		if ( t >= 0 ) {
			if (fabs(hit_point.x - square->p0.x) > (square->side / 2))
				return (-1);
			if (fabs(hit_point.y - square->p0.y) > (square->side / 2))
				return (-1);
			if (fabs(hit_point.z - square->p0.z) > (square->side / 2))
				return (-1);
			return (1);
		} else
			return (-1);
	}
	return (-1);
}
