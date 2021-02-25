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
# define PLANE 1
# define SPH 2
# define SQU 3
# define TRI 4

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

typedef struct 	s_plane
{
	t_vec3f	p0;
	t_vec3f	n;
	t_rgb rgb;
}				t_plane;

typedef struct  s_sphere
{
	t_vec3f cen;
	double	R;
	t_rgb rgb;
}				t_sphere;

typedef struct s_triangle
{
	t_vec3f v0;
	t_vec3f v1;
	t_vec3f v2;
	t_vec3f edge0;
	t_vec3f edge1;
	t_vec3f edge2;
	t_rgb rgb;
}				t_triangle;

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

typedef struct  s_shapes
{
	t_sphere sphere;
	t_plane plane;
	t_square 	squ;
	t_triangle trian;
}				t_shapes;

typedef struct s_objects
{
	double plane;
	double sphere;
	double trian;
	double square;
	int handle;
	double obj1;
	double obj2;
}				t_objects;

typedef struct s_close_obj
{
	double t;
	t_rgb color;
	int type;
	t_vec3f n;
}				t_close_obj;

int 	main(void);
void 	look_at(t_matrix *matrix);
double	make_sphere(t_sphere *sphere, t_camera *cam);
t_sphere	init_sphere(void);
int 	make_square(t_square *square, t_camera *cam);
int 	make_trian(t_triangle *triangle, t_camera *cam);
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
t_vec3f 		mult(t_vec3f a, double b);
void 	closest_object(t_close_obj *close_obj, t_objects *objects);
int 		make_plane(t_plane *plane, t_camera *cam);
t_plane		init_plane(void);
int			rgb_to_color(t_rgb *rgb);
t_triangle	init_trian(void);
void	norm(t_vec3f *vec);
t_vec3f get_shapnorm(t_vec3f n, t_close_obj *close_obj);
t_shapes init_shapes();
int			rgb_to_color(t_rgb *rgb);
t_objects	init_obj(t_shapes *shapes, t_camera *cam);
void	which_shape(t_close_obj *close_obj, t_objects *objects, t_shapes *shapes);
double 		min_t(double a, double b, t_objects *objects, int n);
int		make_all(t_data *img, t_camera *cam, t_resol *resol);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
#endif
