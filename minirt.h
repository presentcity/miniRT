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

typedef struct  data
{
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_data;
/*
typedef struct	centre
{
	double	x;
	double	y;
	double	z;
}				t_centre;
*/
typedef struct	s_scene
{
	double	x;
	double	y;
	double	z;
}				t_scene;

typedef struct	s_norm
{
	double	x;
	double	y;
	double	z;
}				t_norm;

typedef struct  s_sphere
{
	t_scene scene;
	t_norm	norm;
	double	x;
	double	y;
	double	z;
	double	R;
	int		r;
	int		g;
	int		b;
}				t_sphere;

typedef struct	s_vec3f
{
	double	x;
	double	y;
	double	z;
}				t_vec3f;

typedef struct	s_camera
{
	t_vec3f	loc;
	double	fov;
	double	iratio;
}				t_camera;

typedef struct	s_resol
{
	double	x;
	double	y;
}				t_resol;



int 	main(void);
void 	look_at(double forward_x, double forward_y, double forward_z, double **matrix);
double	count_t(t_sphere *sphere, t_camera *cam);
t_sphere	init_sphere(void);
t_camera	init_camera(void);
t_resol		init_resol(void);
t_vec3f		init_vect(void);
int		make_sphere(t_data *img, t_sphere *sphere, t_camera *cam, t_resol *resol);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
#endif
