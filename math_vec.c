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

double		dotproduct(t_vec3f a, t_vec3f b)
{
	return((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

t_vec3f 		mult(t_vec3f a, double b)
{
	t_vec3f c;

	c.x = a.x * b;
	c.y = a.y * b;
	c.z = a.z * b;

	return(c);
}

t_vec3f		matrix_mult(t_vec3f a, t_vec3f b)
{
	t_vec3f c;
	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;

	return(c);
}