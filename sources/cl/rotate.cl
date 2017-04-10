float3			rotate_ray(float3 *ray, t_data *data)
{
	float3	res;
	float3	rad;
	float3	pos;
	float3	matx;
	float3	maty;
	float3	matz;	

	/////////debug
	if (!ROTATE)
	{
		data->offset  = pos;
		return (*ray);
	}
	///////////

	if (data->option == 2 || data->option == 8)
	{
		pos = data->ray_pos - data->pos;
	}
	else
	{
		pos = data->ray_pos - data->obj->pos;
	}
	rad = data->obj->rot * ((float)M_PI / 180.0f);

	if (NATIVE)
	{
		matx = (float3){native_cos(rad.y) * native_cos(rad.z),
		native_cos(rad.y) * (-native_sin(rad.z)),
		native_sin(rad.y)};

		maty = (float3){(-native_sin(rad.x)) * (-native_sin(rad.y)) *
		native_cos(rad.z) + native_cos(rad.x) * native_sin(rad.z),
		(-native_sin(rad.x)) * (-native_sin(rad.y)) * (-native_sin(rad.z)) +
		native_cos(rad.x) * native_cos(rad.z), (-native_sin(rad.x)) *
		native_cos(rad.y)};

		matz = (float3){native_cos(rad.x) * (-native_sin(rad.y)) *
		native_cos(rad.z) + native_sin(rad.x) * native_sin(rad.z),
		native_cos(rad.x) * (-native_sin(rad.y)) * (-native_sin(rad.z)) +
		native_sin(rad.x) * native_cos(rad.z), native_cos(rad.x) *
		native_cos(rad.y)};
	}
	else
	{
		matx = (float3){cos(rad.y) * cos(rad.z),
		cos(rad.y) * (-sin(rad.z)),
		sin(rad.y)};

		maty = (float3){(-sin(rad.x)) * (-sin(rad.y)) * cos(rad.z) +
		cos(rad.x) * sin(rad.z), (-sin(rad.x)) * (-sin(rad.y)) * (-sin(rad.z)) +
		cos(rad.x) * cos(rad.z), (-sin(rad.x)) * cos(rad.y)};

		matz = (float3){cos(rad.x) * (-sin(rad.y)) * cos(rad.z) + sin(rad.x) *
		sin(rad.z), cos(rad.x) * (-sin(rad.y)) * (-sin(rad.z)) + sin(rad.x) *
		cos(rad.z), cos(rad.x) * cos(rad.y)};
	}


	res.x = dot(matx, *ray);
	res.y = dot(maty, *ray);
	res.z = dot(matz, *ray);
	if (data->option > 0)
	{
		data->offset.x = dot(matx, pos);
		data->offset.y = dot(maty, pos);
		data->offset.z = dot(matz, pos);
	}
	if (data->option >= 8)
	{
		data->offset.x = res.x  - dot(matx, pos);
		data->offset.y = res.y  - dot(maty, pos);
		data->offset.z = res.z - dot(matz, pos);
		return (data->offset);
	}

	return(res);
}
