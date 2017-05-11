static float3		reflex_is_light(t_data *data, float3 lightdir,
	global t_lgt *lgt)
{
	float3	light_clr;

	data->ray_pos = lgt->pos;
	data->ray_dir = lightdir;
	touch_object(data);
	if ((data->id == data->save_id &&
		fast_distance(data->save_inter, lgt->pos) < 
		fast_distance(data->intersect, lgt->pos) + PREC))
	{
		data->nl++;
		light_clr = calcul_clr(-lightdir, data->normale, lgt->clr *
			(data->objs[data->id].clr));
		if (data->objs[data->save_id].specular != 0.0f)
			light_clr += is_shining(data->normale, -lightdir, lgt->clr);
		return (light_clr);
	}
	if (fast_distance(data->save_inter, data->save_pos) < 
	fast_distance(data->intersect, data->save_pos) + PREC2)
		data->test++;
	return (0);
}

static float3		reflex_check_all_light(t_data *data)
{
	short	i;
	float3	lightdir;
	float3	rd_light;
	float3	clr;

	i = -1;
	rd_light = 0.0f;
	clr = data->objs[data->id].clr;
	data->normale = calcul_normale(data);
	while (++i < data->n_lgts)
	{
		lightdir = fast_normalize(data->intersect - data->lights[i].pos);
		rd_light += reflex_is_light(data, lightdir, &data->lights[i]);
	}
	rd_light += AMBIANT * clr;
		// PRINT3(rd_light,"light");
	if (!data->nl)
	 	return (rd_light * data->light_reflex_pow);
	else if (data->n_lgts == 1)// || data->n_lgts - data->test == 1)
		return (rd_light / (1.0f + AMBIANT) * data->light_reflex_pow);
	return (rd_light  / (data->n_lgts - data->test + AMBIANT) * data->light_reflex_pow);
}

void	calcul_reflex_ray(t_data *data)
{
	data->light_reflex_pow -= (1.0f - REFLEX);
	if (data->light_reflex_pow == 1.0f)
		data->light_pow -= REFLEX;
	if (data->light_reflex_pow <= 0.0f)
		return;
	data->ray_pos = data->intersect;// - data->ray_dir;
	data->ray_dir = fast_normalize(data->ray_dir - (2.0f * data->normale *
	dot(data->normale, data->ray_dir)));
	touch_object(data);
	save(data);
	data->rd_light += reflex_check_all_light(data);
	// load(data);
}
