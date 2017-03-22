float3			rotate_ray(float3 *ray, t_data *data)
{
	float3	res;
	float3	rad;
	float3	pos;
	float3	matx;
	float3	maty;
	float3	matz;	

	pos = data->obj->pos;
	rad = data->obj->rot * (float)(M_PI / 180.0f);

	_PRINT3(rad, "rad");
	//////debug
	if (ROTATE == 0)
		return (*ray);
	////////////////
	if (float3_to_float(rad) == 0.0f)
		return (*ray);
		
	matx = (float3){cos(rad.y) * cos(rad.z),
	 cos(rad.y) * (-sin(rad.z)),
	  sin(rad.y)};
	maty = (float3){(-sin(rad.x)) * (-sin(rad.y)) * cos(rad.z) + cos(rad.x) * sin(rad.z),
	 (-sin(rad.x)) * (-sin(rad.y)) * (-sin(rad.z)) + cos(rad.x) * cos(rad.z),
	  (-sin(rad.x)) * cos(rad.y)};
	matz = (float3){cos(rad.x) * (-sin(rad.y)) * cos(rad.z) + sin(rad.x) * sin(rad.z),
	 cos(rad.x) * (-sin(rad.y)) * (-sin(rad.z)) + sin(rad.x) * cos(rad.z),
	  cos(rad.x) * cos(rad.y)};

	res.x = dot(matx, *ray);
	res.y = dot(maty, *ray);
	res.z = dot(matz, *ray);
	if (data->option)
	{
		data->offset.x = dot(matx, data->obj->pos);
		data->offset.y = dot(maty, data->obj->pos);
		data->offset.z = dot(matz, data->obj->pos);
		data->offset *= -1;
	}

	_PRINT3(res, "res 1");
	return(res);
}
