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
	if (offset.x > obj->width || offset.y > obj->height)
		ok = 0;
	div = dot(obj->rot, ray_dir);
	if (div == 0.0f)
		*ok = 0;
	t = (-dot(obj->rot, offset)) / div;
	if (t < 0.0f)
		*ok = 0;
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
//	if (ray_dir.y > (0.0f + obj->pos.y))// || /* 0.5 / obj->pos.z ||*/
//			ray_dir.y < -(obj->height - obj->pos.y));// * 0.5 / obj->pos.z)
//		*ok = 0;
	a = dot(ray_dir.xz, ray_dir.xz) - dot(ray_dir.y, ray_dir.y);

	b = 2.0f * (dot(ray_dir.xz, offset.xz) - dot(ray_dir.y, offset.y)) -
		obj->radius * obj->radius;

	c = dot(offset.xz, offset.xz) - dot(offset.y, offset.y);
	if ((delta = calc_delta(a, b, c)) < 0.0f)
		*ok = 0;
	return (norm(delta, ray_pos, ray_dir));
}

float3			ray_cylinder_intersection(global t_obj *obj, float3 ray_pos,
		float3 ray_dir, short *ok)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3	offset;

	offset = ray_pos - obj->pos;
	offset.y = 0;

//	if (ray_dir.y > (obj->height + obj->pos.y) * 0.5f /obj->pos.z ||
//			ray_dir.y < -(obj->height - obj->pos.y) * 0.5f / obj->pos.z)
//		*ok = 0;
	ray_dir.y = 0;
	a = dot(ray_dir, ray_dir);
	b = 2.0f * (dot(ray_dir.xz, offset.xz) - dot(ray_dir.y, offset.y));
	c = dot(offset, offset) - obj->radius * obj->radius;
	if ((delta = calc_delta(a, b, c)) < 0.0f)
		*ok = 0;
	return (norm(delta, ray_pos, ray_dir));
}

float3			ray_sphere_intersection(global t_obj *obj, float3 ray_pos,
		float3 ray_dir, short *ok)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3	offset;

	offset = ray_pos - obj->pos;
	a = dot(ray_dir, ray_dir);
	b = (2.0f * dot(ray_dir.x, offset.x)) + (2.0f * dot(ray_dir.y, offset.y)) +
		(2.0f * dot(ray_dir.z, offset.z));
	c = dot(offset, offset) - (obj->radius * obj->radius);
	if ((delta = calc_delta(a, b, c)) < 0.0f)
		*ok = 0;
	return (norm(delta, ray_pos, ray_dir));
}
