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

typedef struct  data
{
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_data;

typedef struct	centre cen
{
	float	x;
	float	y;
	float	z;
}				t_centre;

typedef struct  sphere
{
	struct	centre;
	float	x;
	float	y;
	float	z;
	float	R;
	float	diam;
	int		r;
	int		g;
	int		b;
}				t_sphere;

typedef	struct	s_nov;
{
	float	x;
	float	y;
	float	z;	
}				t_nov;

typedef struct	camera
{
	float	x;
	float	y;
	float	z;
	float	nov.x;
	float	nov.y;
	float	nov.z;
}				t_camera;

typedef struct	resol
{
	float	x;
	float	y;
}				t_resol;


int 	main(void);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
#endif
