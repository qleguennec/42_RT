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

#include "reflex.cl"
#include "transparency.cl"
#include "lib.cl"
#include "light.h"

unsigned	get_lighting(t_data *data)
{
	float	ambiant = 0.25f;
	float	light_power = 1.0f;
	float3	rd_light = (float3){0.0f, 0.0f, 0.0f};
	short	safe = 0;

	get_color(data, data->objs, data->lgts, data->n_objs, data->n_lgts, &data->intersect,
	 &data->ray_dir, data->id, &light_power, &rd_light, &safe, ambiant);
	return(calcul_rendu_light(rd_light, data->n_lgts, ambiant));

	// get_color(objs, lights, n_objs, n_lights, &ray_pos, &ray_dir,
	// 		obj_ind, &light_power, &rd_light, &safe, ambiant);
	// return(calcul_rendu_light(rd_light, n_lights, ambiant));
}

void	get_color(t_data * data, global t_obj *objs, global t_lgt *lights,
	short n_objs, short n_lights, float3 *ray_pos, float3 *ray_dir,
	short obj_ind, float *light_power, float3 *rd_light, short *safe,
	float ambiant)
{
	(*safe)++;
	if (*light_power > 0.0f && objs[obj_ind].reflex > 0.0f && *safe <= SAFE)
		reflex_calcul(data, objs, lights, n_objs, n_lights, ray_pos,
	 		ray_dir, ambiant, obj_ind, light_power, rd_light, safe);
	if (*light_power > 0.0f && *safe <= SAFE)
		clearness_color(data, objs, lights, n_objs, n_lights, ray_pos,
	 		ray_dir, safe, obj_ind, light_power, rd_light, ambiant);
}

float3		check_all_light(t_data * data, global t_lgt *lights, short n_lights,
	global t_obj *objs, short n_objs, short obj_ind, float ambiant, float3 *ray_dir,
	float3 *ray_pos)
{
	short	i = 0;
	float3	lightdir;
	float3	rd_light;

	rd_light.xyz = (float3)(ambiant, ambiant, ambiant);
	while (i < n_lights)
	{
		lightdir = normalize(*ray_pos - lights[i].pos);
		rd_light += is_light(data, lights[i].pos, lightdir, objs, &lights[i],
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

float3		is_light(t_data * data, float3 lightpos, float3 lightdir, global t_obj *objs, global t_lgt *light,
	short n_objs, short n_lights, float3 normale, short obj_ind)
{
	short	index;
	float3	new_pos;
	float3 light_clr;
	char	cal_light = 0;

	light_clr = light->clr;
	new_pos	= touch_object(data);
	while (index > -1 && index != obj_ind && objs[index].opacity < 1.0f)
	{
		if (cal_light == 0)
		{
		calcul_light(&light_clr, &objs[index]);
		cal_light = 1;
		}
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

float3		calcul_normale(global t_obj *obj, float3 *point)
{
	float3	normale;

	if (obj->type == T_PLANE)
		normale = obj->rot;
	if (obj->type == T_SPHERE)
		normale = obj->pos - *point;
	if (obj->type == T_CYLINDER)
	{
		normale = obj->pos - *point;
		normale.y = 0.0f;
		// normale = rotate_ray(normale, obj->rot);
	}
	if (obj->type == T_CONE)
		normale = (float3){0.0f, 0.0f, 1.0f};
	normale = normalize(normale);
	return (normale);
}
