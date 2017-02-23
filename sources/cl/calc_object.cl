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

float3			norm(float delta, float3 ray_pos, float3 ray_dir)
{
	return (ray_pos + (ray_dir * delta));
}

float3			ray_plane_intersection(global t_obj *obj, float3 ray_pos, float3 ray_dir, short *ok)
{
	float	div;
	float	t;
	float3	offset;

	offset = ray_pos - obj->pos;
	div = dot(obj->rot, ray_dir);
	if (div == 0.0f)
		*ok = -1;
	t = (-dot(obj->rot, offset)) / div;
	if (t < 0.0f)
		*ok = -1;
	return (norm(t, ray_pos, ray_dir));
}

float3			ray_cone_intersection(global t_obj *obj, float3 ray_pos, float3 ray_dir, short *ok)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3	offset;

	offset = ray_pos - obj->pos;
	a = dot(ray_dir.x, ray_dir.x) + dot(ray_dir.z, ray_dir.z)
		- dot(ray_dir.y, ray_dir.y);

	b = 2.0f * (dot(ray_dir.x, offset.x) + dot(ray_dir.z, offset.z) - 
			 dot(ray_dir.y, ray_dir.y));

	c = dot(offset.x, offset.x) + dot(offset.z, offset.z) - dot(offset.y, offset.y);
	if ((delta = calc_delta(a, b, c)) < 0.0f)
		*ok = -1;
	return (norm(delta, ray_pos, ray_dir));
}

float3			ray_cylinder_intersection(global t_obj *obj, float3 ray_pos, float3 ray_dir, short *ok)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3	offset;
	float3	rdir;

	offset = ray_pos - obj->pos;
	offset.y = 0;
	rdir = ray_dir;
	ray_dir.y = 0;
	a = dot(ray_dir, ray_dir);
	b = 2.0f * dot(ray_dir, offset);
	c = dot(offset, offset) - obj->radius * obj->radius;
	if ((delta = calc_delta(a, b, c)) < 0.0f)
		*ok = -1;
	return (norm(delta, ray_pos, rdir));
}

float3			ray_sphere_intersection(global t_obj *obj, float3 ray_pos, float3 ray_dir, short *ok)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3	offset;

//	offset.xy = ray_pos.xy - obj->pos.xy;
//	offset.z = ray_pos.z - (obj->pos.z + 200);
	offset = ray_pos - obj->pos;
	a = dot(ray_dir, ray_dir);
	b = 2.0f * dot(ray_dir, offset);
	c = dot(offset, offset) - (obj->radius * obj->radius);
	if ((delta = calc_delta(a, b, c)) < 0.0f)
		*ok = -1;
	return (norm(delta, ray_pos, ray_dir));
}
