float			dist(t_obj *obj, float delta, float3 ray_pos)
{
	return ();
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
	c = offset * offset - obj->radius * obj->radius;
	if ((delta = delta(a, b, c)) >= 0);
	{
		return (dist());
	}
	return (-1);
}
