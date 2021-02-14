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

t_vec3f		init_vect(void)
{
	t_vec3f	vec;

	vec.x = 0.0;
	vec.y = 0.0;
	vec.z = 0.0;
	return(vec);
}

t_rgb		init_color(void)
{
	t_rgb	rgb;

	rgb.r = 0.0;
	rgb.g = 0.0;
	rgb.b = 0.0;
	return(rgb);
}

t_matrix	init_matr(void)
{
	t_matrix	matrix;

	matrix.forward = (t_vec3f){0.0, 0.0, -1.0};
	matrix.right = (t_vec3f){0.0, 0.0, 0.0};
	matrix.up = (t_vec3f){0.0, 0.0, 0.0};
	matrix.tmp = (t_vec3f){0.0, 1.0, 0.0};
	return(matrix);
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

	camera.loc = (t_vec3f){0.0, 0.0, 1.0};
	camera.fov = 60.0;
	camera.iratio = 0.0;
	camera.dir = (t_vec3f){0.0, 0.0, 0.0};
	return(camera);
}

t_plane		init_plane(void)
{
	t_plane		plane;

	plane.n = (t_vec3f){0.0, -1.0, 0.0};
	plane.p0 = (t_vec3f){0.0, 0.0, 0.0};
	plane.rgb = (t_rgb){0.0, 0.0, 0.0};
	return(plane);
}

t_square		init_square(void)
{
	t_square		square;

	square.n = (t_vec3f){0.0, -1.0, 0.0};
	square.p0 = (t_vec3f){0.0, 0.0, 0.0};
	square.rgb = (t_rgb){0.0, 0.0, 0.0};
	square.side = 0.6;
	return(square);
}

t_triangle	init_trian(void)
{
	t_triangle	triangle;

	triangle.v0 = (t_vec3f){0.0, 0.0, 0.0};
	triangle.v1 = (t_vec3f){-0.1, 0.2, 0.0};
	triangle.v2 = (t_vec3f){-0.1, 0.0, 0.0};
	triangle.edge0 = (t_vec3f){0.0, 0.0, 0.0};
	triangle.edge1 = (t_vec3f){0.0, 0.0, 0.0};
	triangle.edge2 = (t_vec3f){0.0, 0.0, 0.0};
	return(triangle);
}

t_sphere	init_sphere(void)
{
	t_sphere sphere;

	sphere.orig = (t_vec3f){0.3, 0.0, 0.0};
	sphere.scene = (t_vec3f){0.0, 0.0, 1.0};
	sphere.R = 0.1;
	sphere.rgb = (t_rgb){0.0, 0.0, 0.0};
	return (sphere);
}