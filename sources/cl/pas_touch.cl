float3		check_all_light(t_data *data)
{
	short	i = 0;
	float3	lightdir;
	float3	rd_light;

	rd_light = (float3){0.0f, 0.0f, 0.0f};
	while (i < data->n_lgts)
	{
		lightdir = data->intersect - data->lights[i].pos;
		rd_light += is_light(data, lightdir, &data->lights[i],
		calcul_normale(data));
		i++;
	}
	return((float3)(rd_light / (float)(data->nl)) *
		data->objs[data->id].opacity * data->light_pow);
}

float3		is_light(t_data *data, float3 lightdir, global t_lgt *lgt, float3 normale)
{
	short	index = data->id;
	float3	light_clr;

	lightdir = normalize(lightdir);
	// data->ray_pos = lgt->pos;
	// data->ray_dir = -lightdir;
	check_intercept(data, index, 1);
	light_clr = lgt->clr;
	if (data->id > -1 && index != data->id)
	{
		data->ray_pos = data->intersect - data->ray_dir;
		calcul_light(&light_clr, &data->objs[data->id]);
		check_intercept(data, index, 1);
	}
	if (index == data->id)
	{
		data->nl++;
		return (calcul_clr(lightdir, normale, light_clr, &data->objs[index]));
	}
	return (data->ambiant * data->objs[index].clr);
}

unsigned	calcul_rendu_light(t_data *data)
{

	float3	clr;

	clr =  data->rd_light * 255.0f;
	return ((((unsigned)clr.x & 0xff) << 24) + (((unsigned)clr.y & 0xff) << 16)
		+ (((unsigned)clr.z & 0xff) << 8) + ((unsigned)255 & 0xff));
}

void		calcul_light(float3 *light_clr, global t_obj *obj)
{
	*light_clr -= (1.0f - obj->clr) * obj->opacity;
	if (light_clr->x < 0.0f)
		light_clr->x = 0.0f;
	if (light_clr->y < 0.0f)
		light_clr->y = 0.0f;
	if (light_clr->z < 0.0f)
		light_clr->z = 0.0f;
}

float3		calcul_clr(float3 ray, float3 normale, float3 light,
	global t_obj *obj)
{
	float	cosinus;

	cosinus = dot(ray, normale);
	return((float3)(light * cosinus * obj->clr));
}
