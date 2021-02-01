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

t_vector	*color_to_rgb(unsigned int color)
{
    int red;
    int green;
    int blue;

    blue = (int)(color % 256);
    green = (int)(((color - blue) / 256) % 256);
    red = (int)(((color - blue) / (256 * 256)) - green / 256);
    return (new_vector((double)red, (double)green, (double)blue));
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
/*bool intersectPlane(const Vec3f &n, const Vec3f &p0, const Vec3f &l0, const Vec3f &l, float &t)
{
// assuming vectors are all normalized
float denom = dotProduct(n, l);
if (denom > 1e-6) {
Vec3f p0l0 = p0 - l0;
t = dotProduct(p0l0, n) / denom;
return (t >= 0);
}

return false;
}*/

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_plane		init_plane(void)
{
	t_plane		plane;

	plane.n.x = 0.0;
	plane.n.y = 0.0;
	plane.n.z = 1.0;
	plane.p0.x = 0.0;
	plane.p0.y = 0.0;
	plane.p0.z = -10.0;
	return(plane);
}

int 		make_plane(t_sphere *sphere, t_camera *cam)
{
	double denom;
	double t;
	t_plane		plane;
	t_vec3f dif;

	plane = init_plane();
	dif = vec_dif(plane.p0, cam->loc);
	denom = dotproduct(vec_dif(plane.n, cam->loc), sphere->norm);
	if (denom > 1e-6)
	{
		t = dotproduct(dif, plane.n) / denom;
		return (t >= 0);
	}
	return(-1);
}

void 	look_at(double **matrix)
{
	t_vec3f right;
	t_vec3f tmp;
	t_vec3f up;
	t_vec3f forward;

	tmp.y = 1;
	forward.z = -1;
	right = matrix_mult(tmp, forward);
	up = matrix_mult(forward, right);

	matrix[0] = right
	matrix[1] = up;
	matrix[2] = forward;
}

double		count_t(t_sphere *sphere, t_camera *cam)
{
	double t1;
	double t2;
	double t;
	double tca;
	double d2;
	double thc;
	t_vec3f dif;

	dif = vec_dif(sphere->orig, cam->loc);
	tca = dotproduct(dif, sphere->norm);
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

int		make_sphere(t_data *img, t_sphere *sphere, t_camera *cam, t_resol *resol)
{
	double Vw;
	int j;
	double t;
	double *matrix;
	double pix_x = 0, pix_y = 0;
	double n;

	j = 0;
	Vw = 2 * tan(cam->fov/2 * M_PI/180);
	matrix = malloc(sizeof(double *) * 3);
	while (j <= 2)
	{
		matrix[j] = malloc(sizeof(double) * 3);
		j++;
	}
	while (pix_y < resol->y)
	{
		while (pix_x < resol->x)
		{
			cam->iratio = resol->x / resol->y;
			sphere->scene.x = (2 * ((pix_x + 0.5) / resol->x) - 1) * tan(cam->fov / 2 * M_PI / 180) * cam->iratio;
			sphere->scene.y = (1 - 2 * ((pix_y + 0.5) / resol->y) * tan(cam->fov / 2 * M_PI / 180));
			look_at(matrix);
			sphere->norm.x = sphere->scene.x * matrix[0][0] + sphere->scene.y * matrix[1][0] + sphere->scene.z * matrix[2][0] - cam->loc.x;
			sphere->norm.y = sphere->scene.x * matrix[0][1] + sphere->scene.y * matrix[1][1] + sphere->scene.z * matrix[2][1] - cam->loc.y;
			sphere->norm.z = sphere->scene.x * matrix[0][2] + sphere->scene.y * matrix[1][2] + sphere->scene.z * matrix[2][2] - cam->loc.z;
			n = 1/sqrt(pow(sphere->norm.x, 2) + pow(sphere->norm.y, 2) + pow(sphere->norm.z, 2));
			sphere->norm = mult(sphere->norm, n);
			t = count_t(sphere, cam);
			if (t >= 0)
				my_mlx_pixel_put(img, pix_x, pix_y, 0x00FF0000);
			t = make_plane(sphere, cam);
			if (t >= 0)
				my_mlx_pixel_put(img, pix_x, pix_y, 0x00FF0000);
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

	sphere = init_sphere();
	cam = init_camera();
	resol = init_resol();
	vec = init_vect();
	//	if (argc < 2 || argc > 3)
//		printf_error;

// k1 = sqrt(vectorD->x * vectorD->x + vectorD->y * vectorD->y + vectorD->z * vectorD->z); // умножаем вектор D на вектор D
//    k2 = 2 * sqrt(t_sphere->centre->x * vectorD->x + t_sphere->centre->y * vectorD->y + t_sphere->centre->z * vectorD->z); // Умножаем OС на D на вектор D и на 2
//    k3 = sqrt(t_sphere->centre->x * t_sphere->centre->x + t_sphere->centre->y * t_sphere->centre->y + t_sphere->centre->z * t_sphere->centre->z) - pow(t_sphere->R,2); //умножаем вектор OC на вектор
	mlx = mlx_init();
	win = mlx_new_window(mlx, resol.x, resol.y, "How do you do, fellow kids?");
	img.img = mlx_new_image(mlx, resol.x, resol.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
		&img.line_length, &img.endian);
	if (win == 0)
		mlx_destroy_window(mlx, win);
	make_sphere(&img, &sphere, &cam, &resol);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
}
