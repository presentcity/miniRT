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
t_vec3f		*color_to_rgb(unsigned int color)
{
	int red;
	int green;
	int blue;
	t_vec3f color;

	color.b = (int)(color % 256);
	color.g = (int)(((color - blue) / 256) % 256);
	color.r = (int)(((color - blue) / (256 * 256)) - green / 256);
	return (color((double)red, (double)green, (double)blue));
}*/

int			rgb_to_color(t_vec3f *rgb)
{
	int color;

	color = (int)(((int)rgb->x));
	color = (int)((color << 8) + (int)rgb->y);
	color = (int)((color << 8) + (int)rgb->z);
	return (color);
}

