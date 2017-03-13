/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_object.cl                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 11:11:30 by lgatibel          #+#    #+#             */
/*   Updated: 2017/02/13 11:11:39 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj_def.h"
#include "calc.h"
#include "rotate.cl"

float			float3_to_float(float3 v){
	return (v.x + v.y + v.z);
}

void			norm(float *delta, float3 *ray_pos, float3 *ray_dir, float3 *intersect)
{
	*intersect = *ray_pos + (*ray_dir * (*delta));
}

short			ray_plane_intersection(t_data *data, global t_obj *obj)
{
	float	div;
	float	t;
	float3	ray_dir;
	float3	offset;

	ray_dir = data->ray_dir;
	offset = data->ray_pos - obj->pos;
		return (0);
	div = dot(obj->rot, ray_dir);
	if (div == 0.0f)
		return (0);
	t = (-dot(obj->rot, offset)) / div;
	if (t < 0.0f)
		return (0);
	norm(&t, &data->ray_pos, &data->ray_dir, &data->intersect);
	return (1);
}

short			ray_cone_intersection(t_data *data, global t_obj *obj)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3	offset;
	float3 	ray_dir;

	ray_dir = data->ray_dir;
	float	rad;
	// rad = 178.0f * (M_PI / 360.0f);

	float3 pos;
	//float rad;

	rad = obj->rot.z * (M_PI / 180.0f);

	// pos.x = -obj->pos.x;
	// pos.y = obj->pos.y - cos(rad) * obj->pos.z - (sin(rad) * obj->pos.z);
	// pos.z = obj->pos.y - sin(rad) * obj->pos.z + cos(rad) * obj->pos.z;// 
	pos.x = obj->pos.x -(cos(rad) * obj->pos.x + (-sin(rad) * obj->pos.y));
	pos.y = obj->pos.y + (sin(rad) * obj->pos.x - cos(rad) * obj->pos.y);
	pos.z = obj->pos.z;
	offset = -pos;
	ray_dir = rotate_z(&ray_dir, obj);
	// offset = data->ray_pos - obj->pos;
	a = dot(ray_dir.xz, ray_dir.xz) - dot(ray_dir.y, ray_dir.y);// * tan(rad);

	b = (2.0f * dot(ray_dir.x, offset.x)) + (2.0f * dot(ray_dir.z, offset.z)) -
	 (2.0f * dot(ray_dir.y, offset.y));// * tan(rad));

	c = dot(offset.xz, offset.xz) - dot(offset.y, offset.y);// * (tan(rad));
	if ((delta = calc_delta(a, b, c)) < 0.0f)
		return (0);
	norm(&delta, &data->ray_pos, &ray_dir, &data->intersect);

/*	float test = 1.0f;
	if (obj->height > 0.0f && (sqrt(dot(data->intersect - obj->pos,
					data->intersect - obj->pos)) > sqrt((test * obj->height) * (test * obj->height) + obj->radius  * obj->radius) ||
			dot(data->intersect, obj->pos) < 0.0f))
		return (0);
*/	return (1);
}


short			ray_cylinder_intersection(t_data *data, global t_obj *obj)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3	offset;
	float3 	ray_dir;

	ray_dir = data->ray_dir;
	offset = data->ray_pos - obj->pos;
	offset.y = 0;
	float3 rdir;
//	float3 r2dir;
	rdir = ray_dir;
// test rotation
//ne pas changer le ray_dir mtn car on a l'adress
//rotation sur x
	ray_dir = rotate_x(&ray_dir, obj);
//rotation sur y
//	ray_dir = rotate_y(&ray_dir, obj->rot.y);
//rotation sur z
//	ray_dir = rotate_z(&ray_dir, obj);
	rdir = ray_dir;
//
	float3 pos;
	float rad;

	rad = obj->rot.x * (M_PI / 180.0f);

	pos.x = 0;//obj->pos.x;
	pos.y = 0;//obj->pos.y - cos(rad) * obj->pos.z - (sin(rad) * obj->pos.z);
	pos.z = 0;//obj->pos.y - sin(rad) * obj->pos.z + cos(rad) * obj->pos.z;
	offset = pos;
	
	ray_dir.y = 0;
	offset.y = 0;
	a = dot(ray_dir.x, ray_dir.x) + dot(ray_dir.z, ray_dir.z);
	b = (2.0f * dot(ray_dir.x, offset.x)) +
		(2.0f * dot(ray_dir.z, offset.z));
	c = dot(offset.x, offset.x) + dot(offset.z, offset.z) - obj->radius * obj->radius;
	if ((delta = calc_delta(a, b, c)) < 0.0f)
		return (0);


	float t0;
	float t1;
	float y0;
	float y1;
	float tmp;
	tmp = (b * b) - (4.0f * a * c);
	if(tmp < 0.0f)
		return (-1);
	tmp = sqrt(tmp);
	t0 = ((-b + tmp) / (2.0f * a));
	t1 = ((-b - tmp) / (2.0f * a));
	tmp = (t0 > 0.0f && (t0 < t1 || t1 <= 0.0f)) ? t0 : t1;
	/*
	if (t0 > t1)
	{
		tmp = t0;
		t0 = t1;
		t1 = tmp;
	}
	y0 = data->ray_pos.y + (rdir.y * t0);
	y1 = data->ray_pos.y + (rdir.y * t1);
	if (y0 > obj->height)
	{
		if (y1 > obj->height)
			return (0);
		else
		{
			if ((tmp = t0 + (t1 - t0) * (y0 + obj->height) / (y0 - y1)) <= 0.0f)
				return (0);
			norm(&tmp, &data->ray_pos, &ray_dir, &data->intersect);
		}
	}
	else if (y0 >= -obj->height && y0 <= obj->height)
	{
		if (t0 <= 0.0f)
			return (0);
		norm(&t0, &data->ray_pos, &ray_dir, &data->intersect);
	}
	else if (y0 < -obj->height)
	{
		if (y1 < -obj->height)
			return (0);
		else
		{
			if ((tmp = t0 + (t1 - t0) * (y0 - obj->height) / (y0 - y1)) <= 0.0f)
				return (0);
			norm(&tmp, &data->ray_pos, &ray_dir, &data->intersect);
		}
	}
//	norm(delta, data->ray_pos, normalize(rdir), data->intersect);
//	norm(delta, data->ray_pos, normalize(r2dir), data->intersect);
	*/
	return (1);
}
/*
short			ray_cylinder_intersection(t_data *data, global t_obj *obj)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3	offset;
	float3 	ray_dir;

	ray_dir = data->ray_dir;
	offset = data->ray_pos - obj->pos;
	offset.y = 0;
	float3 rdir;
	float3 r2dir;
// test rotation


//	rdir = ray_dir;
//rotation sur x
	ray_dir = rotate_x(&ray_dir, obj->rot.x);
//rotation sur y
//	ray_dir = rotate_y(&ray_dir, obj->rot.y);
//rotation sur z
	ray_dir = rotate_z(&ray_dir, obj->rot.z);


	r2dir = ray_dir;

	ray_dir.y = 0;
	offset.y = 0;
	a = dot(ray_dir, ray_dir);
	b = 2.0f * (dot(ray_dir.xz, offset.xz));
	c = dot(offset, offset) - obj->radius * obj->radius;
	if ((delta = calc_delta(a, b, c)) < 0.0f)
		return (0);
	norm(delta, data->ray_pos, normalize(ray_dir), data->intersect);
//	norm(delta, data->ray_pos, normalize(rdir), data->intersect);
//	norm(delta, data->ray_pos, normalize(r2dir), data->intersect);
	if (obj->height > 0.0f && sqrt(dot(*data->intersect - obj->pos,
		*data->intersect - obj->pos)) >sqrt(obj->height * obj->height +
		obj->radius * obj->radius))
		return (0);
	return (1);
}
*/
short			ray_sphere_intersection(t_data *data, global t_obj *obj)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3	offset;
	float3 	ray_dir;

	ray_dir = data->ray_dir;
	offset = data->ray_pos - obj->pos;
	a = 1.0f;
	b = dot(ray_dir, offset);
	c = dot(offset, offset) - obj->radius * obj->radius;
	if ((delta = (b * b) - a *c) < 0.0f)
		return (0);
	delta = sqrt(delta);
	delta = (-(b + delta) < 0.0f) ? -(b - delta): -(b + delta);
	norm(&delta, &data->ray_pos, &ray_dir, &data->intersect);
	return (1);
}