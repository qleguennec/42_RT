
unsigned	get_lighting(int debug, global t_obj *objs, global t_lgt *lights,
	short n_objs, short n_lights, /*float ambiant, */float3 ray_pos, float3 ray_dir,
	short obj_ind)
{
	float	ambiant = 0.25f;
	short	index = obj_ind;
	float	light_power = 1.0f;
	float3	rd_light = (float3){0.0f, 0.0f, 0.0f};
	short	safe = 0;

	get_color(*objs, *lights, n_objs, n_lights, ray_pos, ray_dir,
			obj_ind, &light_power, &rd_light);
	return(calcul_rendu_light(rd_light, n_lights, ambiant));
}

void	get_color(global t_obj *objs, global t_lgt *lights,
	short n_objs, short n_lights, float3 ray_pos, float3 ray_dir,
	short obj_ind, float3 *light_power, float3 *rd_light)
{
	float3	new_pos = ray_pos;

	safe++;
	if (light_power > 0.0f && objs[obj_ind]->reflex > 0.0f && safe < SAFE)
		rd_light += reflex_calcul(objs, lights, n_objs, n_lights, ray_pos,
	 		ray_dir, ray_dir, obj_ind, &clearness, &rd_light);
	if (light_power > 0.0f && safe < SAFE)
		rd_light += clearness_calcul(objs, lights, n_objs, n_lights, ray_pos,
	 		ray_dir, ray_dir, obj_ind, light_power, rd_light);
}

/*float3	get_color(int debug, global t_obj *objs, global t_lgt *lights,
	short n_objs, short n_lights, float3 ray_pos, float3 ray_dir,
	short obj_ind)
{
	float	light_power = 1.0f;
	float3	rd_light = (float3){0.0f, 0.0f, 0.0f};
	float3	new_pos = ray_pos;

	while (light_power > 0.0f)
	{
		rd_light += check_all_light(lights, n_lights, objs, n_objs, obj_ind, ambiant,
			ray_dir, ray_pos) * * light_power * (1.0f - objs[obj_ind]->reflex);
		light_power *= objs[obj_ind]->reflex;
		calcul_reflex_ray();


	}
		// rd_light += reflex_calcul(debug, objs, lights, n_objs, n_lights, ray_pos,
			// 	ray_dir, ray_dir, obj_ind, &clearness);
	if (light_power > 0.0f)
		rd_light += clearness_calcul(debug, objs, lights, n_objs, n_lights, ray_pos,
	 		ray_dir, ray_dir, obj_ind, &light_power);
	return (rd_color)
}*/
