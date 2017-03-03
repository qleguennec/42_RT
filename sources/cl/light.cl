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


// #include "reflex.cl"
// #include "transparency.cl"
#include "light.h"
#include "calc.h"
#include "obj_def.h"
#include "lib.h"

unsigned	get_lighting(int debug, global t_obj *objs, global t_lgt *lights,
	short n_objs, short n_lights, /*float ambiant, */float3 ray_pos, float3 ray_dir,
	short obj_ind)
{
	float	ambiant = 0.15f;
	float	clearness = 1.0f;
	short	index = obj_ind;
	float3	new_pos = ray_pos;
	float3	rd_light = (float3){0.0f, 0.0f, 0.0f}; //set a la couleur de fondy

//		PRINT3(new_pos,"test position");
	rd_light += check_all_light(lights, n_lights, objs, n_objs, obj_ind, ambiant,
		ray_dir, ray_pos);
	clearness -= (objs[obj_ind].opacity + PREC);
	while (clearness > 0.0f)
	{
		if (index == obj_ind)
			new_pos = touch_object(objs, n_objs, new_pos, ray_dir, &index);
		else if (index == -1)
		{
			rd_light += (float3){0.0f, 0.0f, 0.0f} * clearness;
			clearness = 0.0f;
		}
		else
		{
			obj_ind = index;
			rd_light += (check_all_light(lights, n_lights, objs, n_objs, index, ambiant,
			ray_dir, new_pos) * clearness);
			clearness -= (objs[obj_ind].opacity + PREC);
		}
	}
	return(calcul_rendu_light(rd_light, n_lights, ambiant));
}

float3		check_all_light(global t_lgt *lights, short n_lights,
	global t_obj *objs, short n_objs, short obj_ind, float ambiant, float3 ray_dir,
	float3 ray_pos)
{
	short	i = 0;
	float3	lightdir;
	float3	rd_light;

	rd_light.xyz = (float3)(ambiant, ambiant, ambiant);
	while (i < n_lights)
	{
		lightdir = normalize(ray_pos - lights[i].pos);
		rd_light += is_light(lights[i].pos, lightdir, objs, &lights[i],
		n_objs, n_lights, calcul_normale(&objs[obj_ind], ray_pos), obj_ind);
		i++;
	}
	return((float3)(rd_light / (float)(n_lights + ambiant)) * objs[obj_ind].opacity);
}

unsigned	calcul_rendu_light(float3 light, short n_lights, float ambiant)
{
	float3	clr;

	ambiant = 0;
	clr =  light * 255.0f;
	return ((((unsigned)clr.x & 0xff) << 24) + (((unsigned)clr.y & 0xff) << 16)
		+ (((unsigned)clr.z & 0xff) << 8) + ((unsigned)255 & 0xff));
}

float3		is_light(float3 lightpos, float3 lightdir, global t_obj *objs, global t_lgt *light,
	short n_objs, short n_lights, float3 normale, short obj_ind)
{
	short	index;
	float3	new_pos;
	float3 light_clr;
	char	cal_light = 0;

	light_clr = light->clr;
	new_pos	= touch_object(objs, n_objs, lightpos, lightdir, &index);
	while (index > -1 && index != obj_ind && objs[index].opacity < 1.0f)
	{
		if (cal_light == 0)
		{
		calcul_light(&light_clr, &objs[index]);
		cal_light = 1;
		}
		new_pos = touch_object(objs, n_objs, new_pos, lightdir, &index);
	}
	if (index == obj_ind)
		return (calcul_clr(lightdir, normale, light_clr, &objs[index]));
	else
		return ((float3)(0.0f, 0.0f, 0.0f));
}

void		calcul_light(float3 *light_clr, global t_obj *obj)
{
	*light_clr -= (1.0f - obj->clr) * obj->opacity;
	if (light_clr->x < 0.0f)
		light_clr->x = 0.0f;
	if (light_clr->y < 0.0f)
		light_clr->y = 0.0f;
	if (light_clr->z < 0.0f)
		light_clr->z = 0.0f;
}

float3		calcul_clr(float3 ray, float3 normale, float3 light,
	global t_obj *obj)
{
	float	cosinus;

	cosinus = dot(ray, normale);
	return((float3)(light * cosinus * obj->clr));
}

float3		calcul_normale(global t_obj *obj, float3 point)
{
	float3	normale;

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
