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
	get_color(data);
	return(calcul_rendu_light(data));
}

void	get_color(t_data *data)
{
	data->safe++;
	if (data->light_pow > 0.0f && data->objs[data->id].reflex > 0.0f &&
		data->safe <= SAFE)
		reflex_calcul(data);
	if (data->light_pow > 0.0f && data->safe <= SAFE)
		clearness_color(data);
}

float3		check_all_light(t_data *data)
{
	short	i = 0;
	float3	lightdir;
	float3	rd_light;

	rd_light = (float3){0.0f, 0.0f, 0.0f};
	while (i < data->n_lgts)
	{
		lightdir = normalize(data->intersect - data->lights[i].pos);
		rd_light += is_light(data, lightdir, &data->lights[i],
			calcul_normale(&data->objs[data->id], &data->intersect));
		i++;
	}
	return((float3)(rd_light / (float)(data->n_lgts)) *
		data->objs[data->id].opacity);
}

unsigned	calcul_rendu_light(t_data *data)
{
	float3	clr;

	clr =  data->rd_light / (1 + data->ambiant) * 255.0f;
	return ((((unsigned)clr.x & 0xff) << 24) + (((unsigned)clr.y & 0xff) << 16)
		+ (((unsigned)clr.z & 0xff) << 8) + ((unsigned)255 & 0xff));
}

float3		is_light(t_data *data, float3 lightdir, global t_lgt *lgt, float3 normale)
{
	short	index = data->id;
	float3	old_dir = data->ray_dir;
	float3	old_pos = data->ray_pos;
	float3 light_clr;

	data->ray_pos = lgt->pos;
	data->ray_dir = lightdir;
	touch_object(data);
	light_clr = lgt->clr;
	while (data->id > -1 && index != data->id && data->objs[data->id].opacity < 1.0f)
	{
		calcul_light(&light_clr, &data->objs[data->id]);
		data->ray_pos = data->intersect;
		touch_object(data);
	}
	data->ray_dir = old_dir;
	data->ray_pos = old_pos;
	if (index == data->id)
		return (calcul_clr(lightdir, normale, light_clr, &data->objs[index]));
	else
		data->id = index;
	return (data->ambiant * data->objs[index].clr);
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
	printf("cosinus = %f\n", cosinus);
	return((float3)(light * cosinus * obj->clr));
}

float3		calcul_normale(global t_obj *obj, float3 *point)
{
	float3	normale;

	printf("obj_type = %d", obj->type);
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
