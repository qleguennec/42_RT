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

void			norm(float delta, float3 ray_pos, float3 ray_dir, float3 *intersect)
{
	*intersect = ray_pos + (ray_dir * delta);
}

short			ray_plane_intersection(global t_obj *obj, float3 ray_pos, float3 ray_dir, float3 *intersect)
{
	float	div;
	float	t;
	float3	offset;

	offset = ray_pos - obj->pos;
	div = dot(obj->rot, ray_dir);
	if (div == 0.0f)
		return (0);
	t = (-dot(obj->rot, offset)) / div;
	if (t < 0.0f)
		return (0);
	norm(t, ray_pos, ray_dir, intersect);
	return (1);
}

short			ray_cone_intersection(global t_obj *obj, float3 ray_pos, float3 ray_dir, float3 *intersect)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3	offset;

	offset = ray_pos - obj->pos;
	a = dot(ray_dir.xz, ray_dir.xz) - dot(ray_dir.y, ray_dir.y);

	b = 2.0f * (dot(ray_dir.xz, offset.xz) - dot(ray_dir.y, offset.y)) -
		obj->radius * obj->radius;

	c = dot(offset.xz, offset.xz) - dot(offset.y, offset.y);
	if ((delta = calc_delta(a, b, c)) < 0.0f)
		return (0);

	norm(delta, ray_pos, ray_dir, intersect);
//	obj->height = obj->height * 2.0f;
	float test = 1.0f;
	if (obj->height > 0.0f && (sqrt(dot(*intersect - obj->pos,
					*intersect - obj->pos)) > sqrt((test * obj->height) * (test * obj->height) + obj->radius  * obj->radius) ||
			dot(*intersect, obj->pos) < 0.0f))
		return (0);
	return (1);
}

short			ray_cylinder_intersection(global t_obj *obj, float3 ray_pos,
		float3 ray_dir, float3 *intersect)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3	offset;

	offset = ray_pos - obj->pos;
	offset.y = 0;

	float3 rdir;
	rdir = ray_dir;
//////////////////////////////
	float	rad;
	rad = 90.0f * (M_PI / 180);
//	ray_dir.x = cos(rad) * rdir.x - sin(rad) * rdir.y;
//////////////////////////////
	ray_dir.y = 0;
	a = dot(ray_dir, ray_dir);
	b = 2.0f * (dot(ray_dir.xz, offset.xz) - dot(ray_dir.y, offset.y));
	c = dot(offset, offset) - obj->radius * obj->radius;
	if ((delta = calc_delta(a, b, c)) < 0.0f)
		return (0);
	norm(delta, ray_pos, rdir, intersect);
	if (obj->height > 0.0f && sqrt(dot(*intersect - obj->pos,
		*intersect - obj->pos)) >sqrt(obj->height * obj->height +
		obj->radius * obj->radius))
		return (0);
	return (1);
}

short			ray_sphere_intersection(global t_obj *obj, float3 ray_pos,
		float3 ray_dir, float3 *intersect)
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
		return (0);
	norm(delta, ray_pos, ray_dir, intersect);
	return (1);
}
