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

void	which_shape(t_close_obj *close_obj, t_objects *objects, t_shapes *shapes)
{
	if (objects->plane == 1)
	{
		close_obj->type = PLANE;
		close_obj->color = shapes->plane.rgb;
	}
	if (objects->sphere == 1)
	{
		close_obj->type = SPH;
		close_obj->color = shapes->sphere.rgb;
	}
	if (objects->trian == 1)
	{
		close_obj->type = TRI;
		close_obj->color = shapes->trian.rgb;
	}
	if (objects->square == 1)
	{
		close_obj->type = SQU;
		close_obj->color = shapes->squ.rgb;
	}
}

t_vec3f get_shapnorm(t_vec3f n, t_close_obj *close_obj, t_shapes *shapes)
{
	if (close_obj->type == SPH)
		return(norm(vec_dif(n, shapes->sphere.cen)));
	if (close_obj->type == PLANE)
		return(norm(vec_dif(n, shapes->plane.n)));
	if (close_obj->type == TRI)
		return(norm(vec_dif(n, crossproduct(vec_dif(shapes->trian.v1, \
		shapes->trian.v0), vec_dif(shapes->trian.v2, shapes->trian.v0)))));
	if (close_obj->type == SQU)
		return(norm(vec_dif(n, shapes->square.n)));
}
