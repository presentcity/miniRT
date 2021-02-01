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
	camera.fov = 70.0;
	camera.iratio = 0.0;
	return(camera);
}

t_sphere	init_sphere(void)
{
	t_sphere sphere;

	sphere.orig.x = 0.0;
	sphere.orig.y = 0.0;
	sphere.orig.z = 0.0;
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
	return (sphere);

}