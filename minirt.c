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

/*int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int		get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

int		get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

int		get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

int		get_b(int trgb)
{
	return (trgb & 0xFF);
}

int			rgb_to_color(t_vector *rgb)
{
    int color;

    color = (int)(((int)rgb->x));
    color = (int)((color << 8) + (int)rgb->y);
    color = (int)((color << 8) + (int)rgb->z);
    return (color);
}

void		rearrange_rgb(t_vector *color)
{
	color->x = (color->x > 255) ? 255 : color->x;
	color->x = (color->x < 0) ? 0 : color->x;
	color->y = (color->y > 255) ? 255 : color->y;
	color->y = (color->y < 0) ? 0 : color->y;
	color->z = (color->z > 255) ? 255 : color->z;
	color->z = (color->z < 0) ? 0 : color->z;
}

*/

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int 		make_plane(t_camera *cam)
{
	double denom;
	double t;
	t_plane		plane;
	t_vec3f dif;

	plane = init_plane();
	dif = vec_dif(plane.p0, cam->loc);
	denom = dotproduct(plane.n, cam->dir);
	if (denom < 1e-6)
	{
		t = dotproduct(dif, plane.n) / denom;
		return (t >= 0);
	}
	return(-1);
}

void 	look_at(t_matrix *matrix)
{
	matrix->right = crossproduct(matrix->forward, matrix->tmp);
	matrix->up = crossproduct(matrix->right, matrix->forward);
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

double 		max(double a, double b)
{
	double tmp;

	tmp = a > b ? a : b;
	return(tmp);
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

int		make_all(t_data *img, t_sphere *sphere, t_camera *cam, t_resol *resol)
{
	double Vw;
	int j;
	double t;
	t_matrix	matrix;
	double pix_x = 0, pix_y = 0;
	double n;
	t_triangle	triangle;

	j = 0;
	triangle = init_trian();
	matrix = init_matr();
	Vw = 2 * tan(cam->fov/2 * M_PI/180);
	while (pix_y < resol->y)
	{
		while (pix_x < resol->x)
		{
			cam->iratio = resol->x / resol->y;
			sphere->scene.x = (2 * ((pix_x + 0.5) / resol->x) - 1) * tan(cam->fov / 2 * M_PI / 180) * cam->iratio;
			sphere->scene.y = (1 - 2 * ((pix_y + 0.5) / resol->y)) * tan(cam->fov / 2 * M_PI / 180);
			look_at(&matrix);
			cam->dir = matrix_product(sphere->scene, &matrix, cam);
			n = 1/sqrt(pow(cam->dir.x, 2) + pow(cam->dir.y, 2) + pow(cam->dir.z, 2));
			cam->dir = norm(cam->dir, n);
			//t = max(make_plane(cam), make_sphere(sphere, cam));
			t = make_plane(cam);
			if (t >= 0)
				my_mlx_pixel_put(img, pix_x, pix_y, 0x000000FF);
			t = make_sphere(sphere, cam);
			if (t >= 0)
				my_mlx_pixel_put(img, pix_x, pix_y, 0x00FF0000);
			t = make_trian(&triangle, cam);
			if (t >= 0)
				my_mlx_pixel_put(img, pix_x, pix_y, 0x00ffffff);
			pix_x++;
		}
		pix_x = 0;
		pix_y++;
	}
	return(1);
}

int 	main(void)
{
	void *mlx;
	void *win;
	t_data  img;
	t_sphere	sphere;
	t_camera	cam;
	t_resol		resol;
	t_vec3f		vec;

	vec = init_vect();
	sphere = init_sphere();
	cam = init_camera();
	resol = init_resol();
	mlx = mlx_init();
	win = mlx_new_window(mlx, resol.x, resol.y, "How do you do, fellow kids?");
	img.img = mlx_new_image(mlx, resol.x, resol.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
		&img.line_length, &img.endian);
	if (win == 0)
		mlx_destroy_window(mlx, win);
	make_all(&img, &sphere, &cam, &resol);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
}
