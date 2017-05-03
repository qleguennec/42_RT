static float3         plane_normal(t_data *data, float3 rot)
{
	if (dot(data->ray_dir, rot) > 0.0f)
        return (-rot);
    return (rot);
}

static float3         cone_normal(t_data *data, float3 rot)
{
    float   m;
    float   k;

    // printf("test\n");
    m = dot(data->ray_dir, rot * data->t) + dot(rot, data->offset);
    k = tan((data->objs[data->id].radius / 2.0f) * (float)(M_PI / 180.0f));
    return (data->inter - data->objs[data->id].pos - ((1.0f + k * k) *
    rot * m));
}

static float3         cylinder_normal(t_data *data, float3 rot)
{
    float   m;

	m = dot(data->ray_dir, rot * data->t) + dot(rot, data->offset);
    return (data->inter - data->objs[data->id].pos - rot * m);
}

static float3        calcul_normal_egg(t_data *data)
{
    float3    m;
    float3    k;
    float    a;
    float    b;
    float    k1;
    float    k2;
    float    sr;

   sr = pow(data->objs[data->id].radius, 2.0f);
    data->ray_dir = rotate_ray(&data->ray_dir, data, &data->id);
    k1 = 2.0f * data->objs[data->id].height * (dot(data->ray_dir, data->rot));
    k2 = sr + 2.0f * data->objs[data->id].height *
            dot(data->offset, data->ray_dir) - data->objs[data->id].height;
    a = 4.0f * sr * dot(data->ray_dir, data->ray_dir) - k1 * k1;
    b = 2.0f * (4.0f * sr *    dot(data->ray_dir, data->offset) - k1 * k2);
    m = data->objs[data->id].pos + data->ray_dir * data->objs[data->id].height / 2.0f;
    k = data->intersect - m;
    return(data->objs[data->id].radius - data->ray_dir * (1.0f - pow(b, 2.0f) /
                pow(a, 2.0f) * dot(k, data->ray_dir)));
}

static float3        calcul_normal_paraboloid(t_data *data)
{
    float    m;

   m = dot(data->ray_dir, data->rot) * data->t +
        dot(data->rot, data->offset);
    data->ray_dir = rotate_ray(&data->ray_dir, data, &data->id);
    return(data->intersect - data->objs[data->id].pos - data->ray_dir * m);
}

static float3         sphere_normal(t_data *data)
{
    return (data->inter - data->objs[data->id].pos);
}

float3		        calcul_normale(t_data *data)
{
    float3      rot;

    rot = rotate_ray(&data->rot, data, &data->id);
    if (data->objs[data->id].type == T_PLANE ||
     ((data->objs[data->id].type == T_CONE ||
    data->objs[data->id].type == T_CYLINDER) && data->type == T_DISK))
        return (fast_normalize(plane_normal(data, rot)));
    else if (data->objs[data->id].type == T_CONE)
        return (fast_normalize(cone_normal(data, rot)));
    else if (data->objs[data->id].type == T_CYLINDER)
        return (fast_normalize(cylinder_normal(data, rot)));
	else if (data->objs[data->id].type == T_SPHERE)
        return (fast_normalize(sphere_normal(data)));
	else if (data->objs[data->id].type == T_TORUS)
        return (fast_normalize(calcul_normal_egg(data)));
	else if (data->objs[data->id].type == T_PYRAMID)
        return (fast_normalize(calcul_normal_paraboloid(data)));
	return ((float3){0.0f, 0.0f, 0.0f});
}
