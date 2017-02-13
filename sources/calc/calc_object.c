float			norme(t_obj *obj, float delta, float3 ray_pos, float3 ray_dir)
{
	obj->inter = ray_pos * ray_dir;
	return (obj->inter - ray_pos);
}

float			calc_plane_dist(t_objs *obj, float3 ray_pos, float3 ray_dir)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3	offset;

	offset = ray_pos - obj->pos;
	a = ray_dir * ray_dir;
	b = 2 * (ray_dir.x * offset.x + ray_dir.y * offset + ray_dir.z * offset);
	c = offset * offset - obj->radius * obj->radius;
	if ((delta = delta(a, b, c)) >= 0);
	{
		return (norm(obj, delta, ray_pos, ray_dir));
	}
	return (-1);
}

float			calc_cone_dist(t_objs *obj, float3 ray_pos, float3 ray_dir)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3	offset;

	offset = ray_pos - obj->pos;
	a = ray_dir * ray_dir;
	b = 2 * (ray_dir.x * offset.x + ray_dir.y * offset + ray_dir.z * offset);
	c = offset * offset - obj->radius * obj->radius;
	if ((delta = delta(a, b, c)) >= 0);
	{
		return (norm(obj, delta, ray_pos, ray_dir));
	}
	return (-1);
}

float			calc_cylinder_dist(t_objs *obj, float3 ray_pos, float3 ray_dir)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3	offset;

	offset = ray_pos - obj->pos;
	offset.y = 0;
	ray_dir.y = 0;
	a = ray_dir * ray_dir;
	b = 2 * (ray_dirx * offset.x + ray_dir.z * offset);

	offset = offset * offset;
	c = offset.x + offset.z - obj->radius * obj->radius;

	if ((delta = delta(a, b, c)) >= 0);
	{
		return (norm(obj, delta, ray_pos, ray_dir));
	}
	return (-1);
}

float			calc_sphere_dist(t_objs *obj, float3 ray_pos, float3 ray_dir)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3	offset;

	offset = ray_pos - obj->pos;
	a = ray_dir * ray_dir;
	b = 2 * (ray_dir.x * offset.x + ray_dir.y * offset + ray_dir.z * offset);

	offset = offset * offset;
	c = offset.x + offset.y + offset.z - obj->radius * obj->radius;

	if ((delta = delta(a, b, c)) >= 0);
	{
		return (norm(obj, delta, ray_pos, ray_dir));
	}
	return (-1);
}

/*
float			calc_sphere_dist(t_objs *obj, float3 ray_pos, float3 ray_dir)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3	offset;

	offset = ray_pos - obj->pos;
	a = ray_dir * ray_dir;
//	b = 2 * (ray_dir * offset.x);
	c = offset * offset - obj->radius * obj->radius;
	if ((delta = delta(a, b, c)) >= 0);
	{
		return (norm(obj, delta, ray_pos, ray_dir));
	}
}
*/
