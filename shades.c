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
/*

P = O + closest_t*D  # вычисление пересечения
N = P - closest_sphere.center  # вычисление нормали сферы в точке пересечения
N = N / length(N)
return closest_sphere.color*ComputeLighting(P, N)

ComputeLighting(pix, N) {
    i = 0.0
    while light in scene.Lights {
        if light.type == ambient
        {
		i += light.intensity
		}
        else
        	{
            if light.type == point
                L = light.position - P
            else
                L = light.direction

            n_dot_l = dot(N, L)
            if n_dot_l > 0
                i += light.intensity*n_dot_l/(length(N)*length(L))
        }
    }
    return i
}
*/

/*
t_rgb	color2_coeff(t_rgb a, double n)
{
	t_rgb res;

	res.r = fmin(a.r * n, 1);
	res.g = fmin(a.g * n, 1);
	res.b = fmin(a.b * n, 1);
	return (res);
}

t_rgb	shade(t_scene *scene, t_camera *cam, t_close_obj *close_obj, double t)
{
	t_vec3f		hit_point;
	t_vec3f		hit_normal;
	t_list		*runner;
	t_rgb	res;
	t_rgb	addition;

	res = int_color(0);
	hit_point = vec_summary(cam->loc, mult(cam->dir, t));
	hit_normal = get_shapnorm(hit_point, close_obj);
	if (dotproduct(cam->dir, hit_normal) > 0)
		hit_normal = vec_dif(init_vect(), mult(hit_normal, 1));
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
*/
