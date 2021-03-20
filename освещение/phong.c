

---------- работает цилиндр, но не работает освещение других фигур --------------


t_vec3f 		calc_diff(t_vec3f point, t_vec3f normal, t_vec3f color, t_light *light, t_camera *cam)
{
	t_vec3f lightning = (vec_dif(light->position, point)); //луч, который смотрит от точки на поверхности объекта к источник света.
	t_vec3f ray_to_cam = (vec_dif(cam->loc, point)); // вектор, который исходит из точки на поверхности объекта в камеру (ее положение)
	lightning = norm(lightning); //нормализуем оба вектора
	normal = norm(normal); // нормализуем нормаль объекта, которая к нам пришла. (ненормализованной. Кроме квадрата и плоскости, у них нормали даны изначально нормализованными )
	double vect = dotproduct(ray_to_cam, normal); // скалярное произведение вектора - нормали объекта и вектора, который сморит в камеру. Смотрим, чтобы косинус не был отрицательным, если он отрицательный, значит надо развернуть вектор нормали.
	if (vect > 0)
	{
		normal.x *= -1;
		normal.y *= -1;
		normal.z *= -1;
	}
	double diff_ko = dotproduct(lightning, normal); // скалярное произведение вектора нормали объекта и вектора, который смотрит в источник света.
	if ( diff_ko < 0 )
		diff_ko = 0;
	if ( diff_ko > 1 )
		diff_ko = 1;
	t_vec3f res = mult(color, diff_ko); // умножаем вектор цвета на получишийся коэффициент
	return (res);
}

-------- работает освещение сферы и немного плоскости --------------------


t_vec3f 		calc_diff(t_vec3f point, t_vec3f normal, t_vec3f color, t_light *light)
{
	t_vec3f lightning = (vec_dif(point, light->position));
	double diff_ko = dotproduct(lightning, normal);
	if ( diff_ko < 0 )
		diff_ko = 0;
	if ( diff_ko > 1 )
		diff_ko = 1;
	t_vec3f res = mult(color, diff_ko);
	return (res);
}
