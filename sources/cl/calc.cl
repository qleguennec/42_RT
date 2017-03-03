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

//#include "obj_def.h"
#include "calc.h"
#include "light.h"
#include "light.cl"

#include "calc_object.cl"

float		calc_delta(float a, float b, float c)
{
	float	t0;
	float	t1;
	float	tmp;

	tmp = (b * b) - (4.0f * a * c);
	if(tmp < 0.0f)
		return (-1);
	tmp = sqrt(tmp);
//	printf ("tmp\n", tmp);
	t0 = ((-b + tmp) / (2.0f * a));
	t1 = ((-b - tmp) / (2.0f * a));
	if (t0 > 0.0f && (t0 < t1 || t1 <= 0.0f))
		return (t0);
	return (t1);
}


static float3	ray_intersection(global t_obj *obj, float3 ray_pos,
		float3 ray_dir, short *ok)
{
	if (obj->type == T_PLANE)
		return (ray_plane_intersection(obj, ray_pos, ray_dir, ok));
	else if (obj->type == T_CONE)
		return (ray_cone_intersection(obj, ray_pos, ray_dir, ok));
	else if (obj->type == T_CYLINDER)
		return (ray_cylinder_intersection(obj, ray_pos, ray_dir, ok));
	else if (obj->type == T_SPHERE)
		return (ray_sphere_intersection(obj, ray_pos, ray_dir, ok));
	return (-1);
}

float3	touch_object(global t_obj *tab_objs, short nobjs, float3 ray_pos, float3 ray_dir, short *id)
{
	short			i;
	float			smallest_norm;
	float			norm;
	float3			intersect;
	float3			tmp_intersect;
	short			ok;
	global t_obj	*obj;

	i = -1;
	*id = -1;
	norm = -1;
	smallest_norm = -1;
	intersect = -1;
	while(++i <  nobjs)
	{
		ok = 1;
		obj = &tab_objs[i];
		tmp_intersect = ray_intersection(obj, ray_pos, ray_dir, &ok);
		norm = float3_to_float(tmp_intersect - ray_pos);
		if (ok == 1 && norm > 0.0f && (norm < smallest_norm || smallest_norm == -1))
		{
//			if (obj->type == T_PLANE && dot(tmp_intersect - obj->pos, tmp_intersect - obj->pos) < obj->radius * obj->radius) // formule du disque
				intersect = tmp_intersect;
				smallest_norm = norm;
				*id = i;
		}
	}
	return (intersect);
}

void calc(int debug, global unsigned int *pixel, global t_obj *tab_objs,
	global t_lgt *lgts, short nobjs, short nlgts, float3 ray_pos,
	float3 ray_dir, global t_cam *cam)
{
    short	id;
	float3	intersect;

	id = -1;
	if (debug == 1)
	{
	/*	float3 t;
		float3 t2;
		float t3;
		t = (float3){2, 3, 4};
		t2 = (float3){5, 6, 7};
		t3 = dot(t.xy, t2.xy);
		printf("t3 = [%f]\n",t3);
	*/	//printf("type de lobjet %u\n", tab_objs[0].type);
		// PRINT3(ray_dir,"ray_dir");
	}
    intersect = touch_object(tab_objs, nobjs, ray_pos, ray_dir, &id);
	if (id > -1)
	{
	//	/*
		if (id == 1)
		*pixel = 0xff0000FF;
		else if (id == 2)
		*pixel = 0x00ff00FF;
		else if (id == 3)
		*pixel = 0x00ffffFF;
		else if (id == 3)
		*pixel = 0xffffffFF;
		else if (id == 0)
		*pixel = 0xffff00FF;
		else
		*pixel = 0x0000ffFF;
//		*/
//		PRINT3(intersect,"########inter");
		*pixel = get_lighting(debug, tab_objs, lgts, nobjs, nlgts, intersect, ray_dir, id);
	}
	else
		*pixel = 0x000000FF;
}
