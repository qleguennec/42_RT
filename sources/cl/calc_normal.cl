static float3         plane_normal(t_data *data, float3 rot)
{
	if (dot(data->save_dir, rot) > 0.0f)
        return (-rot);
    return (rot);
}

static float3         cone_normal(t_data *data, float3 rot)
{
    float   m;
    float   k;

    // printf("test\n");
    m = dot(data->save_dir, rot * data->t) + dot(rot, data->save_pos - data->objs[data->save_id].pos);
    k = tan((data->objs[data->save_id].radius / 2.0f) * (float)(M_PI / 180.0f));
    return (data->save_inter - data->objs[data->save_id].pos - ((1.0f + k * k) *
    rot * m));
}

static float3         cylinder_normal(t_data *data, float3 rot)
{
    float   m;

	m = dot(data->save_dir, rot * data->t) + dot(rot, data->save_pos - data->objs[data->save_id].pos);
    return (data->save_inter - data->objs[data->save_id].pos - rot * m);
}

static float3         sphere_normal(t_data *data)
{
    return (data->save_inter - data->objs[data->save_id].pos);
}

float3		        calcul_normale(t_data *data)
{
    float3      rot;
    float3      normale;

    rot = rotate_ray(data, &data->save_id);
    if (data->objs[data->save_id].type == T_PLANE ||
     ((data->objs[data->save_id].type == T_CONE ||
    data->objs[data->save_id].type == T_CYLINDER) && data->type == T_DISK))
        normale = plane_normal(data, rot);
    else if (data->objs[data->save_id].type == T_CONE)
        normale = cone_normal(data, rot);
    else if (data->objs[data->save_id].type == T_CYLINDER)
        normale = cylinder_normal(data, rot);
	else if (data->objs[data->save_id].type == T_SPHERE)
        normale = sphere_normal(data);
	// else if (data->objs[data->save_id].type == T_TORUS)
    //     noirmale = calcul_normal_egg(data);
	// else if (data->objs[data->save_id].type == T_PYRAMID)
    //     normale = calcul_normal_paraboloid(data);
    else 
        normale = 0.0f;
    return (fast_normalize(normale));
}
