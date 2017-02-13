float			norm(t_obj *obj, float delta, float3 ray_pos, float3 ray_dir)
{
	obj->inter = ray_pos * ray_dir;
	return (obj->inter - ray_pos);
}

float			float3_to_float(float3 v){
	return (v.x + v.y + v.z);
}


float			calc_plane_dist(t_objs *obj, float3 ray_pos, float3 ray_dir)
{
	float	a;
	float	b;
	float	c;
	float	div;
	float3	offset;

	offset = ray_pos - obj->pos;
	if ((div = float3_to_float(obj->normal * ray_dir)) == 0)
		return (-1);
	return (float3_to_float(obj->normal * offset) / div);

}

float			calc_cone_dist(t_objs *obj, float3 ray_pos, float3 ray_dir)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3	offset;

	offset = ray_pos - obj->pos;
	a = ray_dir.x * ray_dir.x + ray_dir.y * ray_dir.y + ray_dir.z * ray_dir.z;
	b = 2 * (ray_dir.x * offset.x - ray_dir.y * offset + ray_dir.z * offset);
	- obj->radius * obj->raius; // not sure of that!!
	c = offset * offset - obj->radius * obj->radius;

	a = float3_to_float(ray_dir * ray_dir);
	b = 2 * float3_to_float(ray_dir * offset);
	c = float3_to_float(offset * offset) - obj->radius * obj->radius;

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
	offset = offset * offset;
	a = float3_to_float(ray_dir * ray_dir);
	b = 2 * float3_to_float(ray_dir * offset);
	c = float3_to_float(offset * offset) - obj->radius * obj->radius;
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
	a = float3_to_float(ray_dir * ray_dir);
	b = 2 * float3_to_float(ray_dir * offset);
	c = float3_to_float(offset * offset) - obj->radius * obj->radius;
	if ((delta = delta(a, b, c)) >= 0);
	{
		return (norm(obj, delta, ray_pos, ray_dir));
	}
	return (-1);
}
