#include "minirt.h"

double 		make_plane(t_plane *plane, t_camera *cam)
{
	double denom;
	double t;
	t_vec3f dif;

	dif = vec_dif(plane->p0, cam->loc);
	denom = dotproduct(plane->n, cam->dir);
	if (denom < 1e-6)
	{
		t = dotproduct(dif, plane->n) / denom;
		return (t >= 0);
	}
	return(-1);
}

double 		make_plane1(t_plane *plane, t_cyl *cyl)
{
	double denom;
	double t;
	t_vec3f dif;

	dif = vec_dif(plane->p0, cyl->cen);
	denom = dotproduct(plane->n, cyl->n);
	if (denom < 1e-6)
	{
		t = dotproduct(dif, plane->n) / denom;
		return (t);
	}
	return(-1);
}