#include "minirt.h"

float		length_vec(t_vec3f vector)
{
	return (sqrt(pow(vector.x, 2) + (pow(vector.y, 2) + (pow(vector.z, 2)))));
}

float		dist_vec1(t_vec3f v1, t_vec3f v2)
{
	return (sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2) +
				 pow(v2.z - v1.z, 2)));
}

float		scal_mult_vec(t_vec3f	v1, t_vec3f		v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}
t_vec3f		*subtract_vect(t_vec3f		v1, t_vec3f		v2)
{
	return (&(t_vec3f){(v1.x - v2.x), (v1.y - v2.y), (v1.z - v2.z)});
}

t_vec3f		*mult_vect(t_vec3f v1, float t)
{
	return (&(t_vec3f){(v1.x * t), (v1.y * t), (v1.z * t)});
}

t_vec3f		*cross_vect(t_vec3f v1, t_vec3f v2)
{
	return (&(t_vec3f){(v1.y * v2.z - v1.z * v2.y),
				(v1.z * v2.x - v1.x * v2.z), (v1.x * v2.y - v1.y * v2.x)});
}

t_vec3f		*add_vect1(t_vec3f v1, t_vec3f v2)
{
	return (&(t_vec3f){(v1.x + v2.x), (v1.y + v2.y), (v1.z + v2.z)});
}




float	check_top_plane(t_cyl *cyl, t_vec3f coords, t_vec3f direction)
{
	float		t;
	float		a;
	float		b;
	t_vec3f	*temp;
	t_vec3f	*point;

	a = scal_mult_vec(coords, cyl->n) - (scal_mult_vec(cyl->n,
														  cyl->p1));
	b = scal_mult_vec(direction, cyl->n);
	if (!b)
		return (0);
	t = -a / b;
	temp = mult_vect(direction, t);
	point = add_vect1(coords, *temp);
	a = dist_vec(*point, cyl->p1);
	//free(temp);
	//free(point);
	return (((t > 0) && (a < cyl->D / 2)) ? t : 0);
}

float	check_bottom_plane(t_cyl *cyl, t_vec3f coords, t_vec3f direction)
{
	float		t;
	float		a;
	float		b;
	t_vec3f	*temp;
	t_vec3f	*point;

	a = scal_mult_vec(coords, cyl->n) - (scal_mult_vec(cyl->n,
														  cyl->p0));
	b = scal_mult_vec(direction, cyl->n);
	if (!b)
		return (0);
	t = -a / b;
	temp = mult_vect(direction, t);
	point = add_vect1(coords, *temp);
	a = dist_vec(*point, cyl->p0);
	//free(temp);
	//free(point);
	return (((t > 0) && (a < cyl->D / 2)) ? t : check_top_plane(cyl,
																	  coords, direction));
}

float	check_cyl_side(float t, t_cyl *cyl, t_vec3f coords,
						t_vec3f direction)
{
	t_vec3f	*temp;
	t_vec3f	*xp1;
	t_vec3f	*point;
	float		a1;
	float		a2;

	temp = mult_vect(direction, t);
	point = add_vect1(coords, *temp);
	//free(temp);
	xp1 = subtract_vect(cyl->p0, *point);
	a1 = sqrt(pow(length_vec(*xp1), 2) - pow(cyl->D, 2) / 4);
	//free(xp1);
	xp1 = subtract_vect(cyl->p1, *point);
	a2 = sqrt(pow(length_vec(*xp1), 2) - pow(cyl->D, 2) / 4);
	//free(point);
	//free(xp1);
	if (a1 <= cyl->height && a2 <= cyl->height)
		return (t);
	else
		return (check_bottom_plane(cyl, coords, direction));
}

float	intersec_cylinder(t_cyl *cyl)
{
	float		dis;
	float		t[2];
	float		ret;
	t_vec3f	*dif;
	float		k[5];
	t_vec3f coords = (t_vec3f){0.0, 0.0, -6.0};
	t_vec3f direction = (t_vec3f){0.0, 0.0, 1.0};

	dif = subtract_vect(coords, cyl->cen);
	k[0] = scal_mult_vec(cyl->n, *dif);
	k[1] = scal_mult_vec(direction, cyl->n);
	k[2] = scal_mult_vec(direction, direction) - pow(k[1], 2);
	k[3] = 2 * (scal_mult_vec(direction, *dif) - k[1] * k[0]);
	k[4] = scal_mult_vec(*dif, *dif) - pow(k[0], 2) - pow(cyl->D / 2, 2);
	if ((dis = pow(k[3], 2) - 4 * k[2] * k[4]) < 0)
		return (0);
	t[0] = (-k[3] + sqrt(dis)) / (2 * k[2]);
	t[1] = (-k[3] - sqrt(dis)) / (2 * k[2]);
	ret = t[0] < t[1] ? t[0] : t[1];
	//free_and_null((void **)&dif);
	return (check_cyl_side(ret, cyl, coords, direction));
}