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

float		delta(float a, float b, float c)
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

short	touch_object(global t_obj *tab_objs, short nobjs, float3 ray_pos, float3 ray_dir, float *t)
{
	short	i;
	short	index;
	float	smallest_norm;
	float	norm;
	global t_obj	*obj;

	i = -1;
	index = -1;
	norm = -1;
	smallest_norm = -1;
	while(i++ <  nobjs)
	{
		obj = tab_objs + i;
		norm = ray_norm(obj, ray_pos, ray_dir);
		if (norm > 0 && (norm < smallest_norm || smallest_norm == -1))
		{
			smallest_norm = norm;
			index = i;
			*t = obj->t;
		}
	}
	return (index);
}

void calc(global unsigned int *pixel, global t_obj *tab_objs, global t_lgt *lgts, short nobjs, short nlgts, float3 ray_pos, float3 ray_dir, global t_cam *cam)
{
    short	index;
    float	t;
	float3	intersect;

	printf("ok gros");
    if ((index = touch_object(tab_objs, nobjs, ray_pos, ray_dir, &t)) > -1)
	{
		intersect = ray_pos + ray_dir * t;
		*pixel = 0x00ff00;
	//get_lighting(tab_objs, lgts, nobjs, nlgts, ambiant, intersect, ray_dir, index);
	}
	else
		*pixel = 0x00000000;
}
