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
	plane.rgb = (t_vec3f){0, 0, 255};
	return(plane);
}

t_square		init_square(void)
{
	t_square		square;

	square.n = (t_vec3f){0.0, 1.0, 0.7};
	square.p0 = (t_vec3f){-0.2, 0.0, 0.0};
	square.rgb = (t_vec3f){255, 0, 255};
	square.side = 0.1;
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
	triangle.rgb = (t_vec3f){255, 255, 255};
	triangle.n =(t_vec3f){0.0, 0.0, 0.0};
	return(triangle);
}

t_sphere	init_sphere(void)
{
	t_sphere sphere;

	sphere.cen = (t_vec3f){0.3, 0.0, 0.0};
	sphere.R = 0.1;
	sphere.rgb = (t_vec3f){255, 0, 0};
	sphere.n = (t_vec3f){0, 0, 0};
	return (sphere);
}

t_cyl init_cyl(void)
{
	t_cyl cyl;

	cyl.cen = (t_vec3f){0.0, -0.1, -0.2};
	cyl.n = (t_vec3f){0.0, 1.0, -.5};
	cyl.D = 0.1;
	cyl.height = 2;
	cyl.p0 = (t_vec3f){0.0, 0.0, 0.0};
	cyl.p1 = (t_vec3f){0.0, 0.0, 0.0};
	cyl.rgb = (t_vec3f){0.0, 255, 0.0};
	cyl.norm = (t_vec3f){0.0, 0.0, 0.0};
	return(cyl);
}

t_shapes init_shapes()
{
	t_shapes shapes;
	t_triangle	triangle;
	t_plane		plane;
	t_sphere	sphere;
	t_square square;
	t_cyl cyl;

	cyl = init_cyl();
	sphere = init_sphere();
	triangle = init_trian();
	plane = init_plane();
	square = init_square();
	shapes.cyl = cyl;
	shapes.sphere = sphere;
	shapes.plane = plane;
	shapes.trian = triangle;
	shapes.squ = square;
	return(shapes);
}

t_objects	init_obj(t_shapes *shapes, t_camera *cam)
{
	t_objects objects;

	objects.sphere = make_sphere(&shapes->sphere, cam);
	objects.trian = make_trian(&shapes->trian, cam);
	objects.plane = make_plane(&shapes->plane, cam);
	objects.square = make_square(&shapes->squ, cam);
	objects.cyl = make_cyl(&shapes->cyl, cam, &shapes->plane);
	return(objects);
}

t_light		init_light()
{
	t_light light;

	light.ltype = POINT;
	light.position = (t_vec3f){0.0, -1.0, 0.0};
	light.intensity = 0.4;
	light.color = (t_vec3f){255, 255, 255};
	light.amb = init_amb();
	return (light);
}

t_amb	init_amb()
{
	t_amb amb;

	amb.color = (t_vec3f){255, 255, 255};
	amb.ratio = 0.5;
	return(amb);
}
