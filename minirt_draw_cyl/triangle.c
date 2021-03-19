#include "minirt.h"

static t_vec3f		triangle_normal(t_triangle *trian)
{
	return ((t_vec3f)(crossproduct(trian->edge1, trian->edge0)));
}

double	make_trian(t_triangle *triangle, t_camera *cam)
{
	t_vec3f tvec;
	t_vec3f qvec;
	t_vec3f pvec;
	double v, u, det, invdet, t;

	triangle->n = triangle_normal(triangle);
	triangle->edge0 = vec_dif(triangle->v1, triangle->v0);
	triangle->edge1 = vec_dif(triangle->v2, triangle->v0);
	pvec = crossproduct(cam->dir, triangle->edge1);
	det = dotproduct(triangle->edge0, pvec);
	if (fabs(det) < 1e-6)
		return (-1);
	invdet = 1 / det;
	tvec = vec_dif(cam->loc, triangle->v0);
	u = dotproduct(tvec, pvec) * invdet;
	if (u < 0 || u > 1)
		return (-1);
	qvec = crossproduct(tvec, triangle->edge0);
	v = dotproduct(cam->dir, qvec) * invdet;
	if (v < 0 || u + v > 1)
		return (-1);
	t = dotproduct(triangle->edge1, qvec)* invdet;
	return (1);
}