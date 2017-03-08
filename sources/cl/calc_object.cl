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
		return (0);
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

/* test rotation
*/

	float	rad;
	rad = 178.0f * (M_PI / 360.0f);

	offset = ray_pos - obj->pos;
	a = dot(ray_dir.xz, ray_dir.xz) - dot(ray_dir.y, ray_dir.y) * tan(rad);

	b = 2.0f * (dot(ray_dir.xz, offset.xz) - dot(ray_dir.y, offset.y) * tan(rad));// -
//		obj->radius * obj->radius;

	c = dot(offset.xz, offset.xz) - dot(offset.y, offset.y) * (tan(rad));
	if ((delta = calc_delta(a, b, c)) < 0.0f)
		return (0);
	norm(delta, ray_pos, ray_dir, intersect);

	float test = 1.0f;
	if (obj->height > 0.0f && (sqrt(dot(*intersect - obj->pos,
					*intersect - obj->pos)) > sqrt((test * obj->height) * (test * obj->height) + obj->radius  * obj->radius) ||
			dot(*intersect, obj->pos) < 0.0f))
		return (0);
	return (1);
}

static float3 rotate_x(float3 *ray, angle)
{
	float3	res;
	float	rad;

	rad = angle * (M_PI / 180);
		return (*ray);
	res.x = ray->x;
	res.y = cos(rad) * ray->y - (sin(rad) * ray->z);
	res.z = sin(rad) * ray->y + cos(rad) * ray->z;
	return (res);
}

static float3 rotate_y(float3 *ray, angle)
{
	float3	res;
	float	rad;

	rad = angle * (M_PI / 180);
		return (*ray);
	res.x = cos(rad) * ray->y + sin(rad) * ray->z;
	res.y = ray->y;
	res.z = -(sin(rad) * ray->y) + cos(rad) * ray->z;
	return (res);
}

static float3 rotate_z(float3 * ray, angle)
{
	float3	res;
	float	rad;

	if (angle == 0.0f)
		return (*ray);
	rad = angle * (M_PI / 180);
	res.x = cos(rad) * ray->x - (sin(rad) * ray->y);
	res.y = sin(rad) * ray->x + cos(rad) * ray->y;
	res.z = ray->z;
	return (res);
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
	float3 r2dir;
/* test rotation

*/
	rdir = ray_dir;
//rotation sur x
	ray_dir = rotate_x(&ray_dir, obj->rot.x);
//rotation sur y
	ray_dir = rotate_y(&ray_dir, obj->rot.y);
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
//	norm(delta, ray_pos, normalize(ray_dir), intersect);
	norm(delta, ray_pos, normalize(rdir), intersect);
//	norm(delta, ray_pos, normalize(r2dir), intersect);
/*	if (obj->height > 0.0f && sqrt(dot(*intersect - obj->pos,
		*intersect - obj->pos)) >sqrt(obj->height * obj->height +
		obj->radius * obj->radius))
		return (0);
*/	return (1);
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
	a = 1.0f;
	b = dot(ray_dir, offset);
	c = dot(offset, offset) - obj->radius * obj->radius;
	if ((delta = (b * b) - a *c) < 0.0f)
		return (0);
	delta = sqrt(delta);
	delta = (-(b + delta) < 0.0f) ? -(b - delta): -(b + delta);
	norm(delta, ray_pos, ray_dir, intersect);
	return (1);
}
