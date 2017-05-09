
void	calcul_reflex_ray(t_data *data)
{
	float3	normale;

	normale = calcul_normale(data);
	data->ray_pos = data->intersect - data->ray_dir;
	data->ray_dir = fast_normalize(data->ray_dir - (2.0f * normale *
	dot(normale, data->ray_dir)));
	data->light_pow -= (1.0f - data->objs[data->id].reflex);
	touch_object(data);
}
