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

	dif = vec_dif(sphere->cen
			, cam->loc);
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

int 	make_square(t_square *square, t_camera *cam) {
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
			if ( fabs(hit_point.x - square->p0.x) > (square->side / 2))
				return (-1);
			if ( fabs(hit_point.y - square->p0.y) > (square->side / 2))
				return (-1);
			if ( fabs(hit_point.z - square->p0.z) > (square->side / 2))
				return (-1);
			return (1);
		} else
			return (-1);
	}
	return (-1);
}

/*double	check_top_plane(t_cyl *cyl, t_camera *cam, t_vec3f tmp, t_vec3f point)
{
	double		t;
	double		a;
	double		b;

	a = dotproduct(cam->loc, cyl->n) - (dotproduct(cyl->n,
														  cyl->p1));
	b = dotproduct(cam->dir, cyl->n);
	if (!b)
		return (0);
	t = -a / b;
	tmp = mult(cam->dir, t);
	point = vec_summary(cam->loc, tmp);
	a = dist_vec(point, cyl->p1);
	//free(temp);
	//free(point);
	return (((t > 0) && (a < cyl->D / 2)) ? t : 0);
}

double	check_bottom_plane(t_cyl *cyl, t_camera *cam, t_vec3f tmp, t_vec3f point)
{
	double		t;
	double		a;
	double		b;

	a = dotproduct(cam->loc, cyl->n) - (dotproduct(cyl->n,
														  cyl->p0));
	b = dotproduct(cam->dir, cyl->n);
	if (!b)
		return (0);
	t = -a / b;
	tmp = mult(cam->dir, t);
	point = vec_summary(cam->loc, tmp);
	a = dist_vec(point, cyl->p0);
	//free(temp);
	//free(point);
	return (((t > 0) && (a < cyl->D / 2)) ? t : check_top_plane(cyl, cam, tmp, point));
}


double	cyl_side(double t, t_cyl *cyl, t_camera *cam)
{
	t_vec3f	tmp;
	t_vec3f	xp1;
	t_vec3f	point;
	double		x1;
	double		x2;

	tmp = mult(cam->dir, t);
	point = vec_summary(cam->loc, tmp);
	//free(tmp);
	xp1 = vec_dif(cyl->p0, point);
	x1 = sqrt(pow(veclen(xp1), 2) - pow(cyl->D, 2) / 4);
	xp1 = vec_dif(cyl->p1, point);
	x2 = sqrt(pow(veclen(xp1), 2) - pow(cyl->D, 2) / 4);
	//free((void *)point);
	//free((void *)xp1);
	if (x1 <= cyl->height && x2 <= cyl->height)
		return (t);
	else
		return (check_bottom_plane(cyl, cam, tmp, point));
}

double make_cyl(t_cyl *cyl, t_camera *cam)
{
	double 		dis;
	double		t[2];
	double		res;
	t_vec3f	dif;
	double		k[5];

	cyl->p0 = vec_summary(cyl->cen, (t_vec3f){cyl->height / 2 *
													cam->dir.x, cyl->height / 2 * cam->dir.y, cyl->height / 2 * cam->dir.z});
	cyl->p1 = vec_summary(cyl->cen, (t_vec3f){-cyl->height / 2 *
													  cam->dir.x, -cyl->height / 2 * cam->dir.y, -cyl->height / 2 * cam->dir.z});
	dif = vec_dif(cam->dir, cyl->cen);
	k[0] = dotproduct(cyl->n, dif);
	k[1] = dotproduct(cam->dir, cyl->n);
	k[2] = dotproduct(cam->dir, cam->dir) - pow(k[1], 2);
	k[3] = 2 * (dotproduct(cam->dir, dif) - k[1] * k[0]);
	k[4] = dotproduct(dif, dif) - pow(k[0], 2) - pow((cyl->D / 2), 2);
	if ((dis = pow(k[3], 2) - 4 * k[2] * k[4]) < 0)
		return (0);
	t[0] = (-k[3] + sqrt(dis)) / (2 * k[2]);
	t[1] = (-k[3] - sqrt(dis)) / (2 * k[2]);
	res = t[0] < t[1] ? t[0] : t[1];
	//free_and_null((void **)&dif);
	return (cyl_side(res, cyl, cam));
}*/
