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

*/
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
}	

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


int		make_sphere(img)
{
	float x1 = 99;
	float y1 = 74;
	float z1 = 1;
	float R = 17;
	float t = 0;
	float t1;
	float t2;
	float k1;
	float k2;
	float k3;
	float discr;
	float Vw;
	float Vh;
	float fov;
	float i;
	float j;
	float scene_i;
	float scene_j;
	float scene_z;

	i = 0;
	j = 0;
	fov = 70;
	Vw = 2 * tg(fov/2);
	Vh = Vw;
	pow((x - x1),2) + pow((y - y1),2) + pow((z - z1),2) - pow(R,2);
	while (j < 1080)
	{
		while (i < 1920)
		{
			if (i < 960)
				scene_i = i - 960;
			else
				scene_i = 960 - i;
			if (j > 540)
				scene_j = 540 - j;
			else
				scene_j = j - 540;
			scene_i = scene_i * Vw/1920;
			scene_j = scene_j * Vh/1080;
			k1 = sqrt(pow(scene_i,2) + pow(scene_j,2) + 1); // умножаем вектор D на вектор D
			k2 = 2 * sqrt(x1 * scene_i + y1 * scene_j + 1); // Умножаем OС на D на вектор D и на 2
			k3 = sqrt(pow(x1,2) + pow(y1,2) + pow(z1,2)) - pow(R,2); //умножаем вектор OC на вектор OC
			discr = pow(k2,2) - 4 * k1 * k3;
			if (discr >= 0)
			{
				t1 = -2 * k2 + sqrt(pow(k2,2) - 4 * k1 * k3);
				if (discr == 0)
					break ;
				t2 = -2 * k2 - sqrt(pow(k2,2) - 4 * k1 * k3);
			}
			i++;
		}
		i = 0;
		j++;
		t = t1 < t2 ? t1 : t2;
		if (t)
			my_mlx_pixel_put(&img, i, j, 0x00FF0000);
	}
	return(1);
}

//pow((sphere->x - sphere->centre->x),2) + pow((sphere->y - sphere->centre->y),2) + pow((sphere->z - sphere->centre->z),2) - pow(sphere->R,2); // уравнение сферы радиуса R с центром в t_sphere->centre(С)

int 	main(void)
{
	void *mlx;
	void *win;
	t_data  img;
	int i;
	int j;
	float t;
	t_camera *camera;
	t_sphere *sphere;
	t_resol *resol;

	i = 0;
	j = 0;
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
	while (vector->x < 960)
	{
		vector->z = 1;
		while(vector->y < 540)
		{
			vector = t * vector;
			vector->new_x = t * vector->x;
			sqrt(vector1->x * vector2->x + vector1->y * vector2->y + vector1->z * vector2->z) - r = vector(t*vector->x. t*y. t*z);
			(vector->y)++;
		}
		vector->y = 0;
		(vector->x)++;
	}
	/*
	k1 = sqrt(vectorD->x * vectorD->x + vectorD->y * vectorD->y + vectorD->z * vectorD->z); // умножаем вектор D на вектор D
	k2 = 2 * sqrt(sphere->centre->x * vectorD->x + sphere->centre->y * vectorD->y + sphere->centre->z * vectorD->z); // Умножаем OС на D на вектор D и на 2
	k3 = sqrt(sphere->centre->x * sphere->centre->x + sphere->centre->y * sphere->centre->y + sphere->centre->z * sphere->centre->z) - pow(sphere->R,2); //умножаем вектор OC на вектор OC
	discr = pow(k2,2) - 4 * k1 * k3;
	if (discr >= 0)
	{
		t1 = -2 * k2 + sqrt(pow(k2,2) - 4 * k1 * k3);
		if (discr == 0)
			break ;
		t2 = -2 * k2 - sqrt(pow(k2,2) - 4 * k1 * k3);
		return(t1 < t2 ? t1 : t2);
	} 
	return(NULL);
	// if discr < 0, пересечения нет, а сферы значит тоже нет. 
	while (discr >= 0 && )
	{
		t = check_pix(t_sphere, vectorD);
		x = vectorD->x * t;
		y = vectorD->y * t;
		if (t)
			my_mlx_pixel_put(&img, x, y, 0x00FF0000);
	}
*/
	if (n == c)
	while (i < 99)
	{
		while (j < 99)
		{

			my_mlx_pixel_put(&img, i, j, 0x00FF0000);
			j++;
		}
		j = 0;
		i++;
	}
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
}
