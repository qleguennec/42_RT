static float3         plane_normal(t_data *data, float3 rot)
{
	if (dot(data->ray_dir, rot) > 0.0f)
        return (rot);
    return (-rot); 
}

static float3         cone_normal(t_data *data, float3 rot)
{
    float   m;
    float   k;

    m = dot(data->ray_dir, rot * data->t) + dot(rot, data->offset);
    k = tan((data->objs[data->id].radius / 2.0f) * (float)(M_PI / 180.0f));
    return (data->inter - data->objs[data->id].pos - (1.0f + k * k) *
    rot * m);
}

static float3         cylinder_normal(t_data *data, float3 rot)
{
    float   m;

	m = dot(data->ray_dir, rot * data->t) + dot(rot, data->offset);
    return (data->inter - data->objs[data->id].pos - rot * m);
}

static float3         sphere_normal(t_data *data)
{
    return (data->inter - data->objs[data->id].pos);
}

float3		        calcul_normale(t_data *data)
{
    float3      rot;

    rot = rotate_ray(&data->rot, data, &data->id);
    if (data->objs[data->id].type == T_PLANE)
        return (fast_normalize(plane_normal(data, rot)));
    else if (data->objs[data->id].type == T_CONE)
        return (fast_normalize(cone_normal(data, rot)));
    else if (data->objs[data->id].type == T_CYLINDER)
        return (fast_normalize(cylinder_normal(data, rot)));
    else if (data->objs[data->id].type == T_SPHERE)
        return (fast_normalize(sphere_normal(data)));
	return ((float3){0.0f, 0.0f, 0.0f});
}