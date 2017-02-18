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


// #include "calc.cl"
#include "light.h"
#include "calc.h"
// #include "obj_def.h"
#include "lib.h"

unsigned	get_lighting(global t_obj *objs, global t_lgt *lights,
	short n_objs, short n_lights, /*float ambiant, */float3 ray_pos,
	float3 ray_dir, short obj_ind)
{
	short	i = 0;
	float3	rd_light;
	float	size;
	float3	lightdir;
	float	ambiant = 0.20f;
	// PRINT3(ray_pos,"ray_pos");
	rd_light.xyz = (float3)(ambiant, ambiant, ambiant);
	while (i < n_lights)
	{
		lightdir = normalize(ray_pos - lights[i].pos);
		// PRINT3(ray_pos, "ray_pos");
		rd_light += is_light(lights[i].pos, lightdir, objs, &lights[i],
		n_objs, n_lights, calcul_normale(&objs[obj_ind], ray_pos), obj_ind);
		i++;
	}
	rd_light = rd_light / (float)(n_lights + ambiant);

	// return(calcul_rendu_light(objs[obj_ind].clr, 1));
	return (calcul_rendu_light(rd_light, n_lights));
}
/*
unsigned	twocolor_lerp(float3 a, unsigned b, short pc)
{
	float3	color;

	a = a / pc;
	color.x = 255.0f * (a.x) + (float)(b & 0xff0000) * (1.0f - fmax(a.x, fmax(a.y, a.z)));
	color.y = 255.0f * (a.y) + (float)(b & 0x00ff00) * (1.0f - fmax(a.x, fmax(a.y, a.z)));
	color.z = 255.0f * (a.z) + (float)(b & 0x0000ff) * (1.0f - fmax(a.x, fmax(a.y, a.z)));
	return((((unsigned int)color.x) & 0xff0000) |
			(((unsigned int)color.y) & 0x00ff00) |
			(((unsigned int)color.z) & 0x0000ff));
}
*/
unsigned	calcul_rendu_light(float3 light, short n_lights)
{
	float3	clr;

	clr =  (light / n_lights) * 127.0f;
	return ((((unsigned)clr.x & 0xff) << 24) + (((unsigned)clr.y & 0xff) << 16)
		+ (((unsigned)clr.z & 0xff) << 8) + ((unsigned)255 & 0xff));
}

float3		is_light(float3 lightpos, float3 lightdir, global t_obj *objs, global t_lgt *light,
	short n_objs, short n_lights, float3 normale, short obj_ind)
{
	short	index;

	// PRINT3(lightdir, "lightdir");
	touch_object(objs, n_objs, lightpos, lightdir, &index);
	printf("index 1 : %d\n", obj_ind);
	printf("index 2 : %d\n", index);
	if (index == obj_ind)
		return (calcul_light(lightdir, normale, light, &objs[obj_ind]));
	else
		return ((float3)(0.0f, 0.0f, 0.0f));
}

float3		calcul_light(float3 ray, float3 normale, global t_lgt *light,
	global t_obj *obj)
{
	float	cosinus;

	cosinus = dot(ray, normale);
	return((float3)(light->clr * cosinus * obj->clr));
}

float3		calcul_normale(global t_obj *obj, float3 point)
{
	float3	normale;
	float3 pos_temp;

	if (obj->type == T_PLANE)
		normale = obj->rot;
	if (obj->type == T_SPHERE)
		normale = obj->pos - point;
	if (obj->type == T_CYLINDER)
	{
		normale = obj->pos - point;
		normale.y = 0.0f;
		// normale = rotate_ray(normale, obj->rot);
	}
	if (obj->type == T_CONE)
		normale = (float3){0.0f, 0.0f, 1.0f};
	normale = normalize(normale);
	return (normale);
}
