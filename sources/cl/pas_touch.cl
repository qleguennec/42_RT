

// add de la transparence, pas touche bro's



unsigned	get_lighting(global t_obj *objs, global t_lgt *lights,
	short n_objs, short n_lights, /*float ambiant, */float3 ray_pos, float3 ray_dir,
	short obj_ind)
{
	float	size;
	float	ambiant = 0.0f;
	float	clearness = 1.0f;
	short	index;
	float3	new_pos;

	while (clearness <= 0.0f)
	{
		rd_light += check_all_light(lights, n_lights, objs, obj_ind, ambiant,
			ray_dir, ray_pos)) * clearness;
 		clearness -= ((objs[obj_ind]->opacity + PREC) * clearness); // tester sans le "* clearness" pour un test.
		if (clearness <= 0.0f)
		{
			new_pos = touch_object(objs, n_objs, ray_dir, ray_pos, &index);
			if (index == obj_ind)
				touch_object(objs, n_objs, ray_dir, new_pos, &index);
		rd_light += check_all_light(lights, n_lights, objs, obj_ind, ambiant,
			ray_dir, ray_pos)) * clearness;
		}
	return(calcul_rendu_light(rd_light, n_lights);
}

float3		check_all_light(global t_lgt *lights, short n_lights,
	global t_obj objs, short obj_ind, float ambiant, float3 ray_dir,
	float3 ray_pos)
{
	short	i = 0;
	float3	lightdir;
	float3	rd_light;

	rd_light.xyz = (float3)(ambiant, ambiant, ambiant);
	while (i < n_lights)
	{
		lightdir = normalize(ray_pos - lights[i].pos);
		rd_light += is_light(lights[i].pos, lightdir, objs, &lights[i],
		n_lights, n_objs, calcul_normale(&objs[obj_ind], ray_pos), obj_ind);
		i++;
	}
	return((rd_light / (float)(n_lights + ambiant)) * objs[obj_ind]->opacity);
}


unsigned	get_lighting(global t_obj *objs, global t_lgt *lights,
	short n_objs, short n_lights, /*float ambiant, */float3 ray_pos,
	float3 ray_dir, short obj_ind)
{
	short	i = 0;
	float3	rd_light;
	float	size;
	float3	lightdir;
	float	ambiant = 0.20f;
	// PRINT3(ray_pos,"ray_pos");
	rd_light.xyz = (float3)(ambiant, ambiant, ambiant);
	while (i < n_lights)
	{
		lightdir = normalize(ray_pos - lights[i].pos);
		// PRINT3(ray_pos, "ray_pos");
		rd_light += is_light(lights[i].pos, lightdir, objs, &lights[i],
		n_objs, n_lights, calcul_normale(&objs[obj_ind], ray_pos), obj_ind);
		i++;
	}
	rd_light = rd_light / (float)(n_lights + ambiant);

	// return(calcul_rendu_light(objs[obj_ind].clr, 1));
	return (calcul_rendu_light(rd_light, n_lights, ambiant));
}
