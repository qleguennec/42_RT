float3          rotate_x(float3 *ray, global t_obj *obj, float3 *offset)
{
	float3	res;
	float3		pos;
	float	rad;

	pos = obj->pos;
	if (obj->rot.x == 0.0f)
		return (*ray);
	rad = obj->rot.x * (M_PI / 180.0f);

	offset->x = pos.x;
	offset->y = cos(rad) * pos.y + (-sin(rad) * pos.z);
	offset->z = sin(rad) * pos.y + cos(rad) * pos.z;
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

	offset->x = cos(rad) * pos.x + (sin(rad) * pos.z);
	offset->y = pos.y;
	offset->z = (-sin(rad) * pos.x) + cos(rad) * pos.z;
	*offset *= -1;

	res.x = cos(rad) * ray->y + sin(rad) * ray->z;
	res.y = ray->y;
	res.z = -(sin(rad) * ray->y) + cos(rad) * ray->z;
	return (res);
}
float3          rotate_z(float3 *ray, global t_obj *obj, float3 *offset)
{
	float3	res;
	float	rad;
	float3	pos;

	// pos = *offset;
	pos = obj->pos;

	if (obj->rot.z == 0.0f)
		return (*ray);
	rad = obj->rot.z * (M_PI / 180.0f);

	offset->x = cos(rad) * pos.x + (-sin(rad) * pos.y);//ok
	offset->y = sin(rad) * pos.x + cos(rad) * pos.y;//ok
	offset->z = pos.z;//ok
	*offset *= -1;

	res.x = (cos(rad) * ray->x) + (-sin(rad) * ray->y);
	res.y = (sin(rad) * ray->x) + cos(rad) * ray->y;
	res.z = ray->z;

	float radx = obj->rot.x * (M_PI / 180.0f);
	float3 matx[3] = {{1.0f, 0.0f, 0.0f},
	{0.0f, cos(radx), (-sin(radx))}, 
	{0.0f, sin(radx), cos(radx)}};

	// float3 maty[3] = {{cos(rad), (-sin(rad)), 0.0f}, 
	// {sin(rad), cos(rad), 0.0f},
	// {0.0f, 0.0f, 1.0f}};
	float radz = obj->rot.z * (M_PI / 180.0f);
	float3 matz[3] = {{cos(radz), (-sin(radz)), 0.0f}, 
	{sin(radz), cos(radz), 0.0f},
	{0.0f, 0.0f, 1.0f}};

	float3 mat;
	// mat.x = matx[0].x * matz[0].x + matx[0].y * matz[1].x + matx[0].z * matz[2].x;
	// mat.y = matx[1].x * matz[0].y + matx[1].y * matz[1].y + matx[1].z * matz[2].y;
	// mat.z = matx[2].x * matz[0].z + matx[2].y * matz[1].z + matx[2].z * matz[2].z;

	 mat.x = ray->x * matx[0].x * ray->x * matz[0].x + ray->y * matx[0].y * ray->y * matz[1].x + ray->z * matx[0].z * ray->z * matz[2].x;
	 mat.y = ray->x * matx[1].x * ray->x * matz[0].y + ray->y * matx[1].y * ray->y * matz[1].y + ray->z * matx[1].z * ray->z * matz[2].y;
	 mat.z = ray->x * matx[2].x * ray->x * matz[0].z + ray->y * matx[2].y * ray->y * matz[1].z + ray->z * matx[2].z * ray->z * matz[2].z;

	// res = mat * (*ray);
	// *offset = obj->pos * mat * -1;

	return (normalize(res));
}