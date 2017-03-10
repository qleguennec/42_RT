float3          rotate_x(float3 *ray, global t_obj *obj)
{
	float3	res;
	float3		pos;
	float	rad;

	pos = obj->pos;
	if (obj->rot.x == 0.0f)
		return (*ray);
	rad = obj->rot.x * (M_PI / 180);

	res.x = pos.x;
	res.y = pos.y - cos(rad) * pos.z - (sin(rad) * pos.z);
	res.z = pos.y - sin(rad) * pos.z + cos(rad) * pos.z;

	res.x = ray->x;
	res.y += cos(rad) * ray->y - sin(rad) * ray->z;
	res.z += sin(rad) * ray->y + cos(rad) * ray->z;
	return (res);
}
float3          rotate_y(float3 *ray, global t_obj *obj)
{
	float3	res;
	float	rad;
    float3	pos;

	pos = obj->pos;
	if (obj->rot.y == 0.0f)
		return (*ray);
	rad = obj->rot.y * (M_PI / 180.0f);
	res.x = cos(rad) * ray->y + sin(rad) * ray->z;
	res.y = ray->y;
	res.z = -(sin(rad) * ray->y) + cos(rad) * ray->z;
	return (res);
}
float3          rotate_z(float3 * ray, global t_obj *obj)
{
	float3	res;
	float	rad;
	float3	pos;

	pos = obj->pos;
	if (obj->rot.z == 0.0f)
		return (*ray);
	rad = obj->rot.z * (M_PI / 180.0f);

	res.x = pos.x - cos(rad) * pos.x - (sin(rad) * pos.y);
	res.y = pos.y - sin(rad) * pos.x - cos(rad) * pos.y;
	res.z = pos.z;

	res = normalize(res);
	res.x += cos(rad) * ray->x - (sin(rad) * ray->y);
	res.y += sin(rad) * ray->x + cos(rad) * ray->y;
	res.z = ray->z;
	return (res);
}