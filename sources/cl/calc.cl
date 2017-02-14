/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 17:50:51 by lgatibel          #+#    #+#             */
/*   Updated: 2017/02/13 11:10:55 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj_def.h"
#include "calc.h"
//#include "light.h"

#include "calc_object.cl"

float		calc_delta(float a, float b, float c)
{
	float	t0;
	float	t1;
	float	tmp;

	tmp = sqrt(b * b - (4 * a * c) / (2 * a));
	t0 = (-b + tmp);
	t1 = (-b - tmp);
	if (t1 > 0 && t1 < t0)
		return (t1);
	return (t0);
}


static float	ray_norm(global t_obj *obj, float3 ray_pos, float3 ray_dir)
{
	if (obj->type == T_PLANE)
		return ((obj->t = ray_sphere_norm(obj, ray_pos, ray_dir)));
	else if (obj->type == T_CONE)
		return ((obj->t = ray_cone_norm(obj, ray_pos, ray_dir)));
	else if (obj->type == T_CYLINDER)
		return ((obj->t = ray_cylinder_norm(obj, ray_pos, ray_dir)));
	else if (obj->type == T_SPHERE)
		return ((obj->t = ray_sphere_norm(obj, ray_pos, ray_dir)));
	return (-1);
}

float3	touch_object(global t_obj *tab_objs, short nobjs, float3 ray_pos, float3 ray_dir, float *t, short *id)
{
	short			i;
	float			smallest_norm;
	float			norm;
	float3			intersect;
	float3			tmp_intersect;
	global t_obj	*obj;

	i = -1;
	*id = -1;
	norm = -1;
	smallest_norm = -1;
	while(i++ <  nobjs)
	{
		obj = tab_objs + i;
		tmp_intersect = ray_norm(obj, ray_pos, ray_dir);
		norm = float3_to_float(tmp_intersect - ray_pos);
		if (norm > 0 && (norm < smallest_norm || smallest_norm == -1))
		{
			intersect = tmp_intersect;
			smallest_norm = norm;
			*id = i;
		}
	}
	return (intersect);
}

void calc(global unsigned int *pixel, global t_obj *tab_objs, global t_lgt *lgts, short nobjs, short nlgts, float3 ray_pos, float3 ray_dir, global t_cam *cam)
{
    short	id;
    float	t;
	float3	intersect;

	/*
    touch_object(tab_objs, nobjs, ray_pos, ray_dir, &t, &id);
	if (id > -1)
	{
		*pixel = 0x00ff00;
	//get_lighting(tab_objs, lgts, nobjs, nlgts, intersect, ray_dir, id);
	}
	else
		*pixel = 0x00000000;
	*/
	*pixel = 0xffffff;
}
