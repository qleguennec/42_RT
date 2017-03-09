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

float			float3_to_float(float3 v){
	return (v.x + v.y + v.z);
}

void			norm(float delta, t_data *data)
{
	data->intersect = data->ray_pos + (data->ray_dir * delta);
}

short			ray_plane_intersection(t_data *data, global t_obj *obj)
{
	float	div;
	float	t;
	float3	offset;

	offset = data->ray_pos - obj->pos;
		return (0);
	div = dot(obj->rot, data->ray_dir);
	if (div == 0.0f)
		return (0);
	t = (-dot(obj->rot, offset)) / div;
	if (t < 0.0f)
		return (0);
	norm(t, data);
	return (1);
}

short			ray_cone_intersection(t_data *data, global t_obj *obj)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3	offset;

/* test rotation
*/

	float	rad;
	rad = 178.0f * (M_PI / 360.0f);

	offset = data->ray_pos - obj->pos;
	a = dot(data->ray_dir.xz, data->ray_dir.xz) - dot(data->ray_dir.y, data->ray_dir.y) * tan(rad);

	b = 2.0f * (dot(data->ray_dir.xz, offset.xz) - dot(data->ray_dir.y, offset.y) * tan(rad));// -
//		obj->radius * obj->radius;

	c = dot(offset.xz, offset.xz) - dot(offset.y, offset.y) * (tan(rad));
	if ((delta = calc_delta(a, b, c)) < 0.0f)
		return (0);
	norm(delta, data);

	float test = 1.0f;
	if (obj->height > 0.0f && (sqrt(dot(data->intersect - obj->pos,
					data->intersect - obj->pos)) > sqrt((test * obj->height) * (test * obj->height) + obj->radius  * obj->radius) ||
			dot(data->intersect, obj->pos) < 0.0f))
		return (0);
	return (1);
}

static float3 rotate_x(float3 *ray, global t_obj *obj)
{
	float3	res;
	float3		pos;
	float	rad;

	pos = obj->pos;
	if (obj->rot.x == 0.0f)
		return (*ray);
	rad = obj->rot.x * (M_PI / 180);

	res.x = pos.x;
	res.y = pos.y - cos(rad) * pos.z - (sin(rad) * pos.z);
	res.z = pos.y - sin(rad) * pos.z + cos(rad) * pos.z;

	res.x = ray->x;
	res.y += cos(rad) * ray->y - sin(rad) * ray->z;
	res.z += sin(rad) * ray->y + cos(rad) * ray->z;
	return (res);
}

/*
static float3 rotate_y(float3 *ray, angle)
{
	float3	res;
	float	rad;

	if (angle == 0.0f)
		return (*ray);
	rad = angle * (M_PI / 180);
	res.x = cos(rad) * ray->y + sin(rad) * ray->z;
	res.y = ray->y;
	res.z = -(sin(rad) * ray->y) + cos(rad) * ray->z;
	return (res);
}
*/

static float3 rotate_z(float3 * ray, global t_obj *obj)
{
	float3	res;
	float	rad;
	float3	pos;

	pos = obj->pos;
	if (obj->rot.z == 0.0f)
		return (*ray);
	rad = obj->rot.z * (M_PI / 180.0f);

	res.x = pos.x - cos(rad) * pos.x - (sin(rad) * pos.y);
	res.y = pos.y - sin(rad) * pos.x - cos(rad) * pos.y;
	res.z = pos.z;

	res = normalize(res);
	res.x += cos(rad) * ray->x - (sin(rad) * ray->y);
	res.y += sin(rad) * ray->x + cos(rad) * ray->y;
	res.z = ray->z;
	return (res);
}

short			ray_cylinder_intersection(t_data *data, global t_obj *obj)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3	offset;
	float3	org;

	org = 0;//normalize(obj->pos - obj->pos);
	data->ray_dir -= org;
	offset = data->ray_pos - obj->pos;
	offset.y = 0;
	float3 rdir;
//	float3 r2dir;
	rdir = data->ray_dir;
// test rotation
//ne pas changer le ray_dir mtn car on a l'adress
//rotation sur x
	data->ray_dir = rotate_x(&data->ray_dir, obj);
//rotation sur y
//	data->ray_dir = rotate_y(&data->ray_dir, obj->rot.y);
//rotation sur z
//	data->ray_dir = rotate_z(&data->ray_dir, obj);
	rdir = data->ray_dir;

	data->ray_dir.y = 0;
	offset.y = 0;
	a = dot(data->ray_dir, data->ray_dir);
	b = (2.0f * dot(data->ray_dir.x, offset.x)) +
		(2.0f * dot(data->ray_dir.z, offset.z));
	c = dot(offset, offset) - obj->radius * obj->radius;
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
			norm(tmp, data);
		}
	}
	else if (y0 >= -obj->height && y0 <= obj->height)
	{
		if (t0 <= 0.0f)
			return (0);
		norm(t0, data);
	}
	else if (y0 < -obj->height)
	{
		if (y1 < -obj->height)
			return (0);
		else
		{
			if ((tmp = t0 + (t1 - t0) * (y0 - obj->height) / (y0 - y1)) <= 0.0f)
				return (0);
			norm(tmp, data);
		}
	}
//	norm(delta, data->ray_pos, normalize(rdir), data->intersect);
//	norm(delta, data->ray_pos, normalize(r2dir), data->intersect);
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


	offset = data->ray_pos - obj->pos;
	offset.y = 0;
	float3 rdir;
	float3 r2dir;
// test rotation


//	rdir = data->ray_dir;
//rotation sur x
	data->ray_dir = rotate_x(&data->ray_dir, obj->rot.x);
//rotation sur y
//	data->ray_dir = rotate_y(&data->ray_dir, obj->rot.y);
//rotation sur z
	data->ray_dir = rotate_z(&data->ray_dir, obj->rot.z);


	r2dir = data->ray_dir;

	data->ray_dir.y = 0;
	offset.y = 0;
	a = dot(data->ray_dir, data->ray_dir);
	b = 2.0f * (dot(data->ray_dir.xz, offset.xz));
	c = dot(offset, offset) - obj->radius * obj->radius;
	if ((delta = calc_delta(a, b, c)) < 0.0f)
		return (0);
	norm(delta, data->ray_pos, normalize(data->ray_dir), data->intersect);
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

	offset = data->ray_pos - obj->pos;
	a = 1.0f;
	b = dot(data->ray_dir, offset);
	c = dot(offset, offset) - obj->radius * obj->radius;
	if ((delta = (b * b) - a *c) < 0.0f)
		return (0);
	delta = sqrt(delta);
	delta = (-(b + delta) < 0.0f) ? -(b - delta): -(b + delta);
	norm(delta, data);
	return (1);
}
