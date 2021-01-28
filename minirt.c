/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: presentcity <presentcity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:18:19 by pdrake            #+#    #+#             */
/*   Updated: 2021/01/28 19:52:13 by presentcity      ###   ########.fr       */
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
    return (new_vector((float)red, (float)green, (float)blue));
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


t_struct	init_vect(void)
{
	t_struct	vector;
	
	vector.x = 0.0;
	vector.y = 0.0;
	vector.z = 0.0;
}

t_struct		init_resol(void)
{
	t_struct	resol;
	resol.x = 1920; // изначально ноль
	resol.y = 1080; //изначально ноль
}

t_struct	init_sphere(void)
{
	t_struct	sphere;
	
	sphere.x = 0.0;
	sphere.y = 0.0;
	sphere.z = 0.0;
	sphere.R = 0.0;
	sphere.diam = 0.0;
	sphere.r = 0;
	sphere.g = 0;
	sphere.b = 0;
}	*/

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void 	look_at(float forward_x, float forward_y, float forward_z, float **matrix)
{
	float right_x;
	float right_y;
	float right_z;
	float tmp_x = 0;
	float tmp_y = 1;
	float tmp_z = 0;
	float up_x, up_y, up_z;
	int j = 0;


	matrix = malloc(sizeof(float *) * 3);
	while (j <= 2)
	{
		matrix[j] = malloc(sizeof(float) * 3);
		j++;
	}

	right_x = forward_y * tmp_z - forward_z * tmp_y;
	right_y = forward_z * tmp_x - forward_x * tmp_z;
	right_z = forward_x * tmp_y - forward_y * tmp_x;

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
	matrix[2][2] = forward_y;
}

int		count_t(float norm_i, float norm_j, float norm_z, float x1, float y1, float z1, float R)
{
	float t1;
	float t2;
	float k1;
	float k2;
	float k3;
	float discr;
	float t = 0;

	k1 = sqrt(pow(norm_i,2) + pow(norm_j,2) + pow(norm_z,2));
	k2 = 2 * sqrt(x1 * norm_i + y1 * norm_j + z1 * norm_z);
	k3 = sqrt(pow(x1,2) + pow(y1,2) + pow(z1,2)) - pow(R,2);
	discr = pow(k2,2) - 4 * k1 * k3;
	if (discr >= 0)
	{
		t1 = -2 * k2 + sqrt(pow(k2, 2) - 4 * k1 * k3);
		t2 = -2 * k2 - sqrt(pow(k2, 2) - 4 * k1 * k3);

		t = t1 < t2 ? t1 : t2;
		if ( t > 1 )
			return (t);
		else
			return(-1);
	}
	else
		return(-1);
}

int		make_sphere(void *mlx, void *win, t_data img)
{
	float x1 = 99;
	float y1 = 74;
	float z1 = 1;
	float R = 17;
	float Vw;
	float Vh;
	float fov;
	int i;
	int j;
	float scene_i;
	float scene_j;
	float scene_z = -1;
	float t;
	float forward_x = 0;
	float forward_y = 0;
	float forward_z = 1;
	float **matrix;
	int pix_x, pix_y = 0;

	i = 0;
	j = 0;
	fov = 70;
	Vw = 2 * tan(fov/2);
	Vh = Vw;
	matrix = malloc(sizeof(float *) * 3);
	while (j <= 2)
	{
		matrix[j] = malloc(sizeof(float) * 3);
		j++;
	}
	while (pix_y < 1080)
	{
		while (pix_x < 1920)
		{
			if (pix_y < 960)
				scene_i = pix_x - 960;
			else
				scene_i = 960 - pix_x;
			if (j > 540)
				scene_j = 540 - pix_y;
			else
				scene_j = pix_y - 540;
			scene_i *= Vw/1920;
			scene_j *= Vh/1080;
			look_at(forward_x, forward_y, forward_z, matrix); //делаем матрицу
			while (j < 1 && i <= 2) //каждый элемент вектора перемножаем на соответствующий элемент матрицы
			{
				scene_i *= matrix[j][i];
				i++;
			}
			i = 0;
			j++;
			while (j < 2 && i <= 2)
			{
				scene_j *= matrix[j][i];
				i++;
			}
			i = 0;
			j++;
			while (j == 2 && i <= 2)
			{
				scene_z *= matrix[j][i];
				i++;
			}
			t = count_t(scene_i, scene_j, scene_z, x1, y1, z1, R); //находим точки пересечения графика луча и сферы
			i++;
		}
		pix_x = 0;
		pix_y++;
		if (t > 1)
		{
			my_mlx_pixel_put(&img, pix_x, pix_y, 0x00FF0000);
			mlx_put_image_to_window(mlx, win, img.img, 0, 0);
		}
	}
	return(1);
}


//pow((sphere->x - sphere->centre->x),2) + pow((sphere->y - sphere->centre->y),2) + pow((sphere->z - sphere->centre->z),2) - pow(sphere->R,2); // уравнение сферы радиуса R с центром в t_sphere->centre(С)

int 	main(void)
{
	void *mlx;
	void *win;
	t_data  img;
	float t;
	//t_camera *camera;
	//t_sphere *sphere;
	//t_resol *resol;

	t = 0;
//	if (argc < 2 || argc > 3)
//		printf_error;
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1920, 1080, "How do you do, fellow kids?");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
		&img.line_length, &img.endian);
	if (win == 0)
		mlx_destroy_window(mlx, win);
	make_sphere(mlx, win, img);

	mlx_loop(mlx);
}
