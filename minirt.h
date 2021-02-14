/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrake <pdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:57:01 by pdrake            #+#    #+#             */
/*   Updated: 2021/01/25 14:52:22 by pdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct	s_vec3f
{
	double	x;
	double	y;
	double	z;
}				t_vec3f;

typedef struct	s_rgb
{
	double	r;
	double	g;
	double	b;
}				t_rgb;

typedef struct  s_data
{
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_data;

typedef struct  s_sphere
{
	t_vec3f scene;
	t_vec3f orig;
	double	R;
	t_rgb rgb;
}				t_sphere;

typedef struct 	s_plane
{
	t_vec3f	p0;
	t_vec3f	n;
	t_rgb rgb;
}				t_plane;

typedef struct 	s_square
{
	t_vec3f	p0;
	t_vec3f	n;
	t_rgb rgb;
	double side;
}				t_square;

typedef struct	s_camera
{
	t_vec3f	loc;
	double	fov;
	double	iratio;
	t_vec3f dir;
}				t_camera;

typedef struct	s_resol
{
	double	x;
	double	y;
}				t_resol;

typedef struct	s_matrix
{
	t_vec3f forward;
	t_vec3f up;
	t_vec3f right;
	t_vec3f tmp;
}				t_matrix;

typedef struct s_triangle
{
	t_vec3f v0;
	t_vec3f v1;
	t_vec3f v2;
	t_vec3f edge0;
	t_vec3f edge1;
	t_vec3f edge2;

}				t_triangle;

int 	main(void);
void 	look_at(t_matrix *matrix);
double	make_sphere(t_sphere *sphere, t_camera *cam);
t_sphere	init_sphere(void);
t_square		init_square(void);
t_plane		init_plane(void);
t_camera	init_camera(void);
t_resol		init_resol(void);
t_vec3f		init_vect(void);
t_matrix	init_matr(void);
t_vec3f 	vec_dif(t_vec3f a, t_vec3f b);
t_vec3f 	vec_summary(t_vec3f a, t_vec3f b);
t_vec3f		crossproduct(t_vec3f a, t_vec3f b);
t_vec3f			matrix_product(t_vec3f a, t_matrix *matrix, t_camera *cam);
double		dotproduct(t_vec3f a, t_vec3f b);
t_vec3f 		norm(t_vec3f a, double b);
int 		make_plane(t_camera *cam);
t_plane		init_plane(void);
t_triangle	init_trian(void);
int		make_all(t_data *img, t_sphere *sphere, t_camera *cam, t_resol *resol);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
#endif
