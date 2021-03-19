#include "minirt.h"

/*
t_vec3f		diff_light()
{
	if (!obstacles)
		dotproduct(normal, )
}
*/

t_vec3f 		calc_diff(t_vec3f point, t_vec3f normal, t_vec3f color, t_light *light)
{
	t_vec3f lightning = (vec_dif(point, light->position));
	norm(lightning);
	double diff_ko = dotproduct(lightning, normal);
	if ( diff_ko < 0 )
		diff_ko = 0;
	if ( diff_ko > 1 )
		diff_ko = 1;
	t_vec3f res = mult(color, diff_ko);
	return (res);
/*
	if (light->type == AMBIENT)
	{
		ambient = vec_summary(create_vec(0,0,0), light->amb);
		phong = vec_summary(vec_summary(create_vec(0,0,0), light->amb), diff_light());
		//base_color * phong;
	}
*/
}

t_vec3f		ft_ambient(t_light *light)
{
	t_vec3f res_ambient;
	res_ambient = create_vec(0, 0, 0);
	res_ambient = vec_summary(res_ambient, (t_vec3f){light->amb.ratio * light->amb.color.x/255, light->amb.ratio * light->amb.color.y/255, light->amb.ratio * light->amb.color.z/255});
	return(res_ambient);
}

t_vec3f		ft_phong(t_vec3f point, t_vec3f normal, t_vec3f color, t_light *light)
{
	t_vec3f res;
	t_vec3f diff;
	t_vec3f ambient;

	ambient = mult(ft_ambient(light), 255);
	diff = calc_diff(point, normal, color, light);
	diff.x = (int)diff.x;
	diff.y = (int)diff.y;
	diff.z = (int)diff.z;
	ambient.x = (int)ambient.x;
	ambient.y = (int)ambient.y;
	ambient.z = (int)ambient.z;
	color.x /= 255;
	color.y /= 255;
	color.z /= 255;
	res = vec_mult(color,vec_summary(ambient, diff));
	norm(res);
	return(res);
}
