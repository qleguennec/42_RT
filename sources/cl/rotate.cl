float3			rotate_ray(float3 *ray, t_data *data)
{
	float3	res;

	data->rad = data->obj->rot * (float)(M_PI / 180.0f);
	float3 rad = data->rad;
	_PRINT3(rad, "rad");
	//////debug
	if (ROTATE == 0)
		return (*ray);
	///////debug
	if (float3_to_float(data->rad) == 0.0f)
		return (*ray);
	////////////////////////////////////matrice de rotation;
	float3 matx = (float3){cos(rad.x), 0.0f, sin(rad.z)};
	float3 maty = (float3){(-sin(rad.z) * (-sin(rad.x))), cos(rad.y), (-sin(rad.z) * cos(rad.z))};
	float3 matz = (float3){cos(rad.z) * (-sin(rad.z)), sin(rad.y), cos(rad.z) * cos(rad.z)};

	matx = (float3){cos(rad.x), 0.0f, sin(rad.z)};
	maty = (float3){(-sin(rad.x) * (-sin(rad.x))), cos(rad.y), (-sin(rad.z) * cos(rad.z))};
	matz = (float3){cos(rad.x) * (-sin(rad.x)), sin(rad.y), cos(rad.z) * cos(rad.z)};
	_PRINT3(*ray, "ray or");
	_PRINT3(matx, "matx");
	_PRINT3(maty, "maty");
	_PRINT3(matz, "matz");
	res.x = dot(matx , *ray);
	res.y = dot(maty, *ray);
	res.z = dot(matz, *ray);
	_PRINT3(res, "res 1");
	
	///////////////////////////////////
	//  res = rotate_x(ray, data->rad.x);
	// res = rotate_y(ray, data->rad.y);
	//  res = rotate_z(&res, data->rad.z);
	//  rotate_pos_x(data);
	// rotate_pos_y(data);
	//  rotate_pos_z(data);
	_PRINT3(res, "res 2");
	return(res);
}
//
void			rotate_pos_x(t_data *data)
{
	float3	pos;

	pos = data->obj->pos;
	////////////////////////test de rotation sur x puis z
	// data->offset.x = cos(data->rad.x) * pos.x + pos.y + pos.z;
	// data->offset.y = (-sin(data->rad.x) * (-sin(data->rad.x))) * pos.x + cos(data->rad.x) * pos.y + ((-sin(data->rad.x)) * cos(data->rad.x)) * pos.z;
	// data->offset.z = cos(data->rad.x) * (-sin(data->rad.x)) * pos.x + sin(data->rad.x) * pos.y + cos(data->rad.x) * cos(data->rad.x) * pos.z;
	////////////////////////////////////////////////////////////////////////////////
	data->offset.x = cos(data->rad.x) * pos.x + (-sin(data->rad.x)) * pos.y + 0;
	data->offset.y = (cos(data->rad.x) * sin(data->rad.x)) * pos.x + cos(data->rad.x) * cos(data->rad.x) * pos.y + (-sin(data->rad.x)) * pos.z;
	data->offset.z = sin(data->rad.x) * sin(data->rad.x) * pos.x + sin(data->rad.x) * cos(data->rad.x) * pos.y + cos(data->rad.x) * pos.z;
	/////////////////////////////////
	// data->offset.x = pos.x;
	// data->offset.y = cos(data->rad.x) * pos.y + (-sin(data->rad.x) * pos.z);
	// data->offset.z = sin(data->rad.x) * pos.y + cos(data->rad.x) * pos.z;
	data->offset *= -1;
}

float3          rotate_x(float3 *ray, float rad)
{
	float3	res;

	////////////////////////test de rotation sur x puis z
	res.x = cos(rad) * ray->x + (-sin(rad)) * ray->y + 0;
	res.y = (cos(rad) * sin(rad)) * ray->x + cos(rad) * cos(rad) * ray->y + (-sin(rad)) * ray->z;
	res.z = sin(rad) * sin(rad) * ray->x + sin(rad) * cos(rad) * ray->y + cos(rad) * ray->z;
	///////////////////////////////////////////////////////////////

	/////////////////////////////////
	// res.x = ray->x;
	// res.y = cos(rad) * ray->y + (-sin(rad) * ray->z);
	// res.z = sin(rad) * ray->y + cos(rad) * ray->z;

	return (fast_normalize(res));
}

void          rotate_pos_y(t_data *data)
{
    float3	pos;

	pos = data->offset;
	data->offset.x = cos(data->rad.y) * pos.x + (sin(data->rad.y) * pos.z);
	data->offset.y = pos.y;
	data->offset.z = (-sin(data->rad.y) * pos.x) + cos(data->rad.y) * pos.z;
	data->offset *= -1;
}

float3          rotate_y(float3 *ray, float rad)
{
	float3	res;

	res.x = cos(rad) * ray->y + sin(rad) * ray->z;
	res.y = ray->y;
	res.z = -(sin(rad) * ray->y) + cos(rad) * ray->z;
	return (res);
}

void          rotate_pos_z(t_data *data)
{
	float3	pos;

	// pos = data->offset;
	pos = data->obj->pos;
	// data->offset.x = data->offset.x -( cos(data->rad.z) * pos.x +
	//  (-sin(data->rad.z) * pos.y));
	// data->offset.y = data->offset.y -(sin(data->rad.z) * pos.x +
	//  cos(data->rad.z) * pos.y);
	// data->offset.z = 0;

	data->offset.x = cos(data->rad.z) * pos.x + (-sin(data->rad.z) * pos.y);
	data->offset.y = sin(data->rad.z) * pos.x + cos(data->rad.z) * pos.y;
	data->offset.z = pos.z;
	data->offset *= -1;
}

////////////////////////////////enlever l'offset et le rajouter dans la structure'
float3          rotate_z(float3 *ray, float rad)
{
	float3	res;

	res.x = (cos(rad) * ray->x) + (-sin(rad) * ray->y);
	res.y = (sin(rad) * ray->x) + cos(rad) * ray->y;
	res.z = ray->z;

	// float radx = obj->rot.x * (M_PI / 180.0f);
	// float3 matx[3] = {{1.0f, 0.0f, 0.0f},
	// {0.0f, cos(radx), (-sin(radx))},
	// {0.0f, sin(radx), cos(radx)}};

	// // float3 maty[3] = {{cos(rad), (-sin(rad)), 0.0f},
	// // {sin(rad), cos(rad), 0.0f},
	// // {0.0f, 0.0f, 1.0f}};
	// float radz = obj->rot.z * (M_PI / 180.0f);
	// float3 matz[3] = {{cos(radz), (-sin(radz)), 0.0f},
	// {sin(radz), cos(radz), 0.0f},
	// {0.0f, 0.0f, 1.0f}};

	// float3 mat;
	// // mat.x = matx[0].x * matz[0].x + matx[0].y * matz[1].x + matx[0].z * matz[2].x;
	// // mat.y = matx[1].x * matz[0].y + matx[1].y * matz[1].y + matx[1].z * matz[2].y;
	// // mat.z = matx[2].x * matz[0].z + matx[2].y * matz[1].z + matx[2].z * matz[2].z;

	//  mat.x = ray->x * matx[0].x * ray->x * matz[0].x + ray->y * matx[0].y * ray->y * matz[1].x + ray->z * matx[0].z * ray->z * matz[2].x;
	//  mat.y = ray->x * matx[1].x * ray->x * matz[0].y + ray->y * matx[1].y * ray->y * matz[1].y + ray->z * matx[1].z * ray->z * matz[2].y;
	//  mat.z = ray->x * matx[2].x * ray->x * matz[0].z + ray->y * matx[2].y * ray->y * matz[1].z + ray->z * matx[2].z * ray->z * matz[2].z;

	// res = mat * (*ray);
	// *offset = obj->pos * mat * -1;

	return (fast_normalize(res));
	}
