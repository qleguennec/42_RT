/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erodrigu <erodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 15:39:48 by erodrigu          #+#    #+#             */
/*   Updated: 2017/02/09 15:39:48 by erodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

include "light.h";
include "calc.h"
include "obj_types.h"

unsigned get_lighting(global t_obj *objs, global t_obj *lights,
	short n_objs, short n_lights, float ambiant, float3 ray_pos, float3 ray_dir,
	short obj_ind)
{
	short	i = 0;
	float3	rd_light;
	float	size;
	float3	lightdir;

	rd_light.xyz = (ambiant, ambiant, ambiant);
	while (i < n_lgts)
	{
		lightdir = normalize(ray_pos - lights[i]->pos);
		rd_light += is_light(lights[i]->pos, lightdir, b_objs, b_lgts[i],
		n_lgts, n_objs, calcul_normale(objs[obj_ind], ray_pos), obj_ind);
		i++;
	}
	rd_light = rd_light / (float)(n_lights + ambiant);
	return (((rd_light.x & 0xff) << 16) + ((rd_light.y & 0xff) << 8) +
		(rd_light.z & 0xff));
}

float3	is_light(float3 lightpos, float3 lightdir, global t_obj *objs, global t_obj *light,
	short n_objs, short n_lights, float3 normale, short obj_ind)
{
	short	index;

	index = touch_object(objs, n_objs, lightpos, lightdir, &index);
	if (index == obj_ind)
		return (calcul_light(lightdir, normale, light, objs[obj_ind]));
	else
		return ((float3)(0.0f, 0.0f, 0.0f));
}

float3	calcul_light(float3 *ray, float3 *normale, global t_obj *light,
	global t_obj *obj)
{
	float	cosinus;

	cosinus = my_dot(ray, normale);
	return((float3)(light->col * cosinus * obj->col));
}

float	my_dot(float3 *v1, float3 *v2)
{
	return (ray->x * normale->x + ray->y * normale->y + ray->z * normale->z);
}

float3	calcul_normale(t_obj *obj, float3 point)
{
	float3	normale;
	float3 pos_temp;

	if (obj->type == T_PLAN)
		normale = obj->rot;
	if (obj->type == T_SPHERE)
		normale = obj->pos - point;
	if (obj->type == T_CYLINDER)
	{
		pos_temp = (obj->pos.x, 0, obj.pos.z);
		normale = pos_temp - point;
		normale = rotate_ray(normale, obj->rot);
	}
	normale = normalize(normale);
	return (normale);
}
