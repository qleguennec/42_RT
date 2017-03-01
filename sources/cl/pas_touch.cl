
unsigned	get_lighting(int debug, global t_obj *objs, global t_lgt *lights,
	short n_objs, short n_lights, /*float ambiant, */float3 ray_pos, float3 ray_dir,
	short obj_ind)
{
	float	ambiant = 0.25f;
	short	index = obj_ind;

	get_color();

	return(calcul_rendu_light(rd_light, n_lights, ambiant));
}

float3	get_color(int debug, global t_obj *objs, global t_lgt *lights,
	short n_objs, short n_lights, float3 ray_pos, float3 ray_dir,
	short obj_ind)
{
	float	light_power = 1.0f;
	float3	rd_light = (float3){0.0f, 0.0f, 0.0f};
	float3	new_pos = ray_pos;

	if (light_power > 0.0f)
		rd_light += reflex_calcul(debug, objs, lights, n_objs, n_lights, ray_pos,
	 		ray_dir, ray_dir, obj_ind, &clearness);
	if (light_power > 0.0f)
		rd_light += clearness_calcul(debug, objs, lights, n_objs, n_lights, ray_pos,
	 		ray_dir, ray_dir, obj_ind, &light_power);
	return (rd_color)
}


float3	reflex_calcul(int debug, global t_obj *objs, global t_lgt *lights,
	short n_objs, short n_lights, float3 ray_pos, float3 ray_dir,
	short obj_ind)
{

	rd_light += check_all_light(lights, n_lights, objs, n_objs, obj_ind, ambiant,
		ray_dir, ray_pos) * (1.0f - objs[obj_ind]->reflex);
	light_power *= objs[obj_ind]->reflex;
	calcul_reflex_ray();
}

float3	calcul_refract_ray()
{

}

float3	calcul_refract_ray()
{

}

float3	clearness_color(int debug, global t_obj *objs, global t_lgt *lights,
	short n_objs, short n_lights, float3 ray_pos, float3 ray_dir,
	short obj_ind, float *light_power)
{
	short	index = obj_ind;
	float3	new_pos = ray_pos;
	float3	rd_light = (float3){0.0f, 0.0f, 0.0f};

	rd_light += check_all_light(lights, n_lights, objs, n_objs, obj_ind,
		ambiant, ray_dir, ray_pos)
	light_power -= (objs[obj_ind].opacity);
	// ray_dir = calcul_reffract();
	rd_light += clearness_calcul(objs, lights, n_objs, n_lights, ray_pos,
		ray_dir, ray_dir, obj_ind, &light_power, &rd_light);
	if (light_power > 0.0f)
		get_color();
	return (rd_light);
}

void	clearness_calcul(global t_obj *objs, global t_lgt *lights,
	short n_objs, short n_lights, float3 *new_pos, float3 ray_dir,
	short obj_ind, float *light_power, float3 *rd_light)
{
	while (index == obj_ind)
		new_pos = touch_object(objs, n_objs, new_pos, ray_dir, &index);
	if (index == -1)
	{
		*rd_light += (float3){1.0f, 1.0f, 1.0f} * light_power;
		light_power = 0.0f;
	}
	else
	{
		obj_ind = index;
		*rd_light += (check_all_light(lights, n_lights, objs, n_objs, index,
			ambiant, ray_dir, new_pos) * light_power);
		light_power -= (objs[obj_ind].opacity);
		ray_dir = calcul_reffract();
	}
}
