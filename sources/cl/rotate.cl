float3          rotate_x(float3 *ray, global t_obj *obj, float3 *offset)
{
	float3	res;
	float3		pos;
	float	rad;

	pos = obj->pos;
	if (obj->rot.x == 0.0f)
		return (*ray);
	rad = obj->rot.x * (M_PI / 180.0f);

	offset->x = obj->pos.x;
	offset->y = cos(rad) * obj->pos.y + (-sin(rad) * obj->pos.z);
	offset->z = sin(rad) * obj->pos.y + cos(rad) * obj->pos.z;
	*offset *= -1;

	res.x = ray->x;
	res.y = cos(rad) * ray->y + (-sin(rad) * ray->z);
	res.z = sin(rad) * ray->y + cos(rad) * ray->z;
	return (normalize(res));
}
float3          rotate_y(float3 *ray, global t_obj *obj, float3 *offset)
{
	float3	res;
	float	rad;
    float3	pos;

	pos = obj->pos;
	if (obj->rot.y == 0.0f)
		return (*ray);
	rad = obj->rot.y * (M_PI / 180.0f);

	offset->x = cos(rad) * obj->pos.x + (sin(rad) * obj->pos.z);
	offset->y = obj->pos.y;
	offset->z = (-sin(rad) * obj->pos.x) + cos(rad) * obj->pos.z;
	*offset *= -1;

	res.x = cos(rad) * ray->y + sin(rad) * ray->z;
	res.y = ray->y;
	res.z = -(sin(rad) * ray->y) + cos(rad) * ray->z;
	return (res);
}
float3          rotate_z(float3 * ray, global t_obj *obj, float3 *offset)
{
	float3	res;
	float	rad;
	float3	pos;

	pos = obj->pos;
	if (obj->rot.z == 0.0f)
		return (*ray);
	rad = obj->rot.z * (M_PI / 180.0f);

	offset->x = cos(rad) * obj->pos.x + (-sin(rad) * obj->pos.y);//ok
	offset->y = sin(rad) * obj->pos.x + cos(rad) * obj->pos.y;//ok
	offset->z = obj->pos.z;//ok
	*offset *= -1;

	res.x = (cos(rad) * ray->x) + (-sin(rad) * ray->y);
	res.y = (sin(rad) * ray->x) + cos(rad) * ray->y;
	res.z = ray->z;
	return (normalize(res));
}