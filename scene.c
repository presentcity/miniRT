/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrake <pdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:18:19 by pdrake            #+#    #+#             */
/*   Updated: 2021/01/25 19:50:33 by pdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int 		make_plane(t_plane *plane, t_camera *cam)
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

double		make_sphere(t_sphere *sphere, t_camera *cam)
{
	double t1;
	double t2;
	double t;
	double tca;
	double d2;
	double thc;
	t_vec3f dif;

	dif = vec_dif(sphere->orig, cam->loc);
	tca = dotproduct(dif, cam->dir);
	if (tca < 0)
		return (-1);
	d2 =  dotproduct(dif, dif) - pow(tca,2);
	if (d2 > pow(sphere->R,2))
		return -1;
	thc = sqrt(pow(sphere->R,2) - d2);
	t1 = tca - thc;
	t2 = tca + thc;
	if (t1 < 0 && t2 < 0)
		return -1;
	if (t1 > 0 && t2 > 0)
		t = t1 < t2 ? t1 : t2;
	else
		t = t1 < t2 ? t2 : t1;
	return (t);
}

int 	make_trian(t_triangle *triangle, t_camera *cam)
{
	t_vec3f tvec;
	t_vec3f qvec;
	t_vec3f pvec;
	double v, u, det, invdet, t;

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

int 	make_square(t_square *square, t_camera *cam)
{
	double	denom;
	t_vec3f	hit_point;
	t_vec3f	p0l0;
	double t;

	denom = dotproduct(square->n, cam->dir);
	if (denom < 1e-6)
	{
		p0l0 = vec_dif(square->p0, cam->loc);
		t = dotproduct(p0l0, square->n) / denom;
		hit_point = vec_summary(cam->loc, mult(cam->dir, t));
		if (t >= 0)
		{
			if (fabs(hit_point.x - square->p0.x) > (square->side / 2))
				return (-1);
			if (fabs(hit_point.y - square->p0.y) > (square->side / 2))
				return (-1);
			if (fabs(hit_point.z - square->p0.z) > (square->side / 2))
				return (-1);
			return (1);
		}
		else
			return (-1);
	}
	return (-1);
}