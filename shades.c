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

t_rgb	color2_coeff(t_rgb a, double n)
{
	t_rgb res;

	res.r = fmin(a.r * n, 1);
	res.g = fmin(a.g * n, 1);
	res.b = fmin(a.b * n, 1);
	return (res);
}

t_rgb	shade(t_scene *scene, t_camera *cam, t_close_obj *close_obj, double t_min)
{
	t_vec3f		hit_point;
	t_vec3f		hit_normal;
	t_list		*runner;
	t_rgb	result;
	t_rgb	addition;

	result = int_color(0);
	hit_point = vec_summary(cam->loc, mult(cam->dir, t_min));
	hit_normal = get_normal(hit_point, close_obj);
	if (dotproduct(cam->dir, hit_normal) > 0)
		hit_normal = vec_dif(create_vec(0, 0, 0), mult(hit_normal, 1));
	runner = scene->lights;
	while (runner != NULL)
	{
		addition = light_contribution(*(t_light *)(runner->content),
									  new_inter(hit_point, hit_normal, closest_object, cam),
									  *scene);
		result = color2_add(result, addition);
		runner = runner->next;
	}
	return (result);
}

int			get_color(t_scene *scene, t_ray sent, t_close_obj *close_obj)
{
	double		t_min;
	t_rgb	result;
	t_rgb	ambient_color;

	if (intersect_with_all(scene->objects, sent, &closest_object, &t_min))
	{
		ambient_color = color2_coeff(scene->ambient_color,
									 scene->ambient_intensity);
		result = color2_add(color2_mult(closest_object->color, ambient_color),
							shade(scene, sent, closest_object, t_min));
		return (to_int(result));
	}
	else
		return (0);
}
