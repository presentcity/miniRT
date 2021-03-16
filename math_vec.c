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

t_vec3f 	vec_dif(t_vec3f a, t_vec3f b)
{
	t_vec3f c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;

	return(c);
}

t_vec3f 	vec_summary(t_vec3f a, t_vec3f b)
{
	t_vec3f c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;

	return(c);
}

double		dotproduct(t_vec3f a, t_vec3f b)
{
	return((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

t_vec3f		create_vec(double x, double y, double z)
{
	t_vec3f new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_vec3f 		mult(t_vec3f a, double b)
{
	t_vec3f c;

	c.x = a.x * b;
	c.y = a.y * b;
	c.z = a.z * b;

	return(c);
}

t_vec3f			matrix_product(t_vec3f a, t_matrix *matrix, t_camera *cam)
{
	t_vec3f norm;

	norm.x = (a.x * matrix->right.x + a.y * matrix->up.x + a.z * matrix->forward.x) - cam->loc.x;
	norm.y = (a.x * matrix->right.y + a.y * matrix->up.y + a.z * matrix->forward.y) - cam->loc.y;
	norm.z = (a.x * matrix->right.z + a.y * matrix->up.z + a.z * matrix->forward.z) - cam->loc.z;

	return(norm);
}

t_vec3f		crossproduct(t_vec3f a, t_vec3f b)
{
	t_vec3f c;
	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;

	return(c);
}

void	norm(t_vec3f vec)
{
	double len;

	len = sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;
}

double 		veclen(t_vec3f vec)
{
	return (sqrt(pow(vec.x, 2) + (pow(vec.y, 2) + (pow(vec.z, 2)))));
}

double		dist_vec(t_vec3f a, t_vec3f b)
{
	return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) +
				 pow(b.z - a.z, 2)));
}