/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: presentcity <presentcity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:18:19 by pdrake            #+#    #+#             */
/*   Updated: 2021/01/29 22:52:55 by presentcity      ###   ########.fr       */
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
t_vec3f		init_vect(void)
{
	t_vec3f	vec;
	
	vec.x = 0.0;
	vec.y = 0.0;
	vec.z = 0.0;
	return(vec);
}

t_resol		init_resol(void)
{
	t_resol		resol;

	resol.x = 1920;
	resol.y = 1080;
	return(resol);
}

t_camera	init_camera(void)
{
	t_camera	camera;

	camera.loc.x = 0.0;
	camera.loc.y = 0.0;
	camera.loc.z = 1.0;
	camera.fov = 80.0;
	camera.iratio = 0.0;
	return(camera);
}

t_sphere	init_sphere(void)
{
	t_sphere	sphere;
	
	sphere.x = 0.0;
	sphere.y = 0.0;
	sphere.z = 0.3;
	sphere.scene.x = 0.0;
	sphere.scene.y = 0.0;
	sphere.scene.z = 1;
	sphere.norm.x = 0.0;
	sphere.norm.y = 0.0;
	sphere.norm.z = 0.0;
	sphere.R = 0.1;
	sphere.r = 0;
	sphere.g = 0;
	sphere.b = 0;
	return(sphere);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void 	look_at(double forward_x, double forward_y, double forward_z, double **matrix)
{
	double right_x;
	double right_y;
	double right_z;
	double tmp_x = 0;
	double tmp_y = 1;
	double tmp_z = 0;
	double up_x, up_y, up_z;

	right_x = tmp_y * forward_z - tmp_z * forward_y;
	right_y = tmp_z * forward_x - tmp_x * forward_z;
	right_z = tmp_x * forward_y - tmp_y * forward_x;

	up_x = forward_y * right_z - forward_z * right_y;
	up_y = forward_z * right_x - forward_x * right_z;
	up_z = forward_x * right_y - forward_y * right_x;

	matrix[0][0] = right_x;
	matrix[0][1] = right_y;
	matrix[0][2] = right_z;
	matrix[1][0] = up_x;
	matrix[1][1] = up_y;
	matrix[1][2] = up_z;
	matrix[2][0] = forward_x;
	matrix[2][1] = forward_y;
	matrix[2][2] = forward_z;
}

double		count_t(t_sphere *sphere, t_camera *cam)
{
	double t1;
	double t2;
	double t;
	double tca;
	double d2;
	double thc;

	tca = (sphere->x - cam->loc.x) * sphere->norm.x + (sphere->y - cam->loc.y) * sphere->norm.y + (sphere->z - cam->loc.z) * sphere->norm.z;  // скалярное произведение векторов;
	if (tca < 0)
		return (-1);
	d2 = (pow((sphere->x - cam->loc.x),2) + pow((sphere->y - cam->loc.y),2) + pow((sphere->z - cam->loc.z),2)) - pow(tca,2);
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
	double forward_x = 0;
	double forward_y = 0;
	double forward_z = -1;
	double **matrix;
	int pix_x = 0, pix_y = 0;

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
		{/*
			if (pix_x < resol->x / 2)
				sphere->scene.x = pix_x - resol->x / 2;
			else
				sphere->scene.x = resol->x / 2 - pix_x;
			if (pix_y > resol->y / 2)
				sphere->scene.y = resol->y / 2 - pix_y;
			else
				sphere->scene.y = pix_y - resol->y / 2;
			sphere->scene.x *= Vw/resol->x * (resol->x / resol->y);
			sphere->scene.y *= Vw/resol->y;*/
			cam->iratio = resol->x / resol->y;
			sphere->scene.x = (2 * ((pix_x + 0.5) / resol->x) - 1) * tan(cam->fov / 2 * M_PI / 180) * cam->iratio;
			sphere->scene.y = (1 - 2 * ((pix_y + 0.5) / resol->y) * tan(cam->fov / 2 * M_PI / 180));
			look_at(forward_x, forward_y, forward_z, matrix);
			sphere->norm.x = sphere->scene.x * matrix[0][0] + sphere->scene.y * matrix[1][0] + sphere->scene.z * matrix[2][0] - cam->loc.x;
			sphere->norm.y = sphere->scene.x * matrix[0][1] + sphere->scene.y * matrix[1][1] + sphere->scene.z * matrix[2][1] - cam->loc.y;
			sphere->norm.z = sphere->scene.x * matrix[0][2] + sphere->scene.y * matrix[1][2] + sphere->scene.z * matrix[2][2] - cam->loc.z;
			sphere->norm.x *= 1/sqrt(pow(sphere->norm.x, 2) + pow(sphere->norm.y, 2) + pow(sphere->norm.z, 2));
			sphere->norm.y *= 1/sqrt(pow(sphere->norm.x, 2) + pow(sphere->norm.y, 2) + pow(sphere->norm.z, 2));
			sphere->norm.z *= 1/sqrt(pow(sphere->norm.x, 2) + pow(sphere->norm.y, 2) + pow(sphere->norm.z, 2));
			t = count_t(sphere, cam);
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
