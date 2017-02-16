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

float			norm(global t_obj *obj, float delta, float3 ray_pos, float3 ray_dir)
{
	return (float3_to_float((ray_pos + ray_dir)) * delta);
}

float			ray_plane_norm(global t_obj *obj, float3 ray_pos, float3 ray_dir)
{
	float	div;
	float3	offset;

	offset = ray_pos - obj->pos;
	if ((div = float3_to_float(obj->rot * ray_dir)) == 0)
		return (-1);
	return (float3_to_float(obj->rot * offset) / div);

}

float			ray_cone_norm(global t_obj *obj, float3 ray_pos, float3 ray_dir)
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
	if ((delta = calc_delta(a, b, c)) >= 0)
	{
		return (norm(obj, delta, ray_pos, ray_dir));
	}
	return (-1);
}

float			ray_cylinder_norm(global t_obj *obj, float3 ray_pos, float3 ray_dir)
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
	if ((delta = calc_delta(a, b, c)) >= 0)
		return (norm(obj, delta, ray_pos, ray_dir));
	return (-1);
}

float			ray_sphere_norm(global t_obj *obj, float3 ray_pos, float3 ray_dir)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3	offset;

	offset = ray_pos - obj->pos;
	a = float3_to_float(ray_dir * ray_dir);
	b = 2 * float3_to_float(ray_dir * offset);
	//c = float3_to_float(offset * offset) - obj->radius * obj->radius;
	c = float3_to_float(offset * offset) - (float)400;
	if ((delta = calc_delta(a, b, c)) >= 0)
		return (norm(obj, delta, ray_pos, ray_dir));
	return (-1);
}
