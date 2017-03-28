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
	init_laputain_desamere(data);
	get_color(data);
	return(calcul_rendu_light(data));
}

void	init_laputain_desamere(t_data *data)
{
	// data->objs[0].reflex = 1.0f;
	// data->objs[1].reflex = 1.0f;
	// data->objs[2].reflex = 1.0f;
	// data->objs[3].reflex = 1.0f;
	data->objs[4].reflex = 0.90f;
	// data->objs[5].reflex = 1.0f;
	// data->objs[6].reflex = 1.0f;
}

void	get_color(t_data *data)
{
	while (data->safe > 0 && data->light_pow > 0.0f)
	{
		if (data->light_pow > 0.0f && data->objs[data->id].reflex > 0.0f)
		{
			// printf("data->id = %u\n",data->id);
			reflex_calcul(data);
		}
		 else if (data->light_pow > 0.0f)
	 		clearness_color(data);
	}
}

float3		check_all_light(t_data *data)
{
	short	i = 0;
	float3	lightdir;
	float3	rd_light;

	rd_light = (float3){0.0f, 0.0f, 0.0f};
	if (i < data->n_lgts)
	{
		lightdir = data->intersect - data->lights[i].pos;
		rd_light += is_light(data, lightdir, &data->lights[i],
		calcul_normale(data));
		i++;
	}
	return((float3)(rd_light / (float)(data->nl)) *
		data->objs[data->id].opacity * data->light_pow);
}

unsigned	calcul_rendu_light(t_data *data)
{
	float3	clr;

	clr =  data->rd_light * 255.0f;
	return ((((unsigned)clr.x & 0xff) << 24) + (((unsigned)clr.y & 0xff) << 16)
		+ (((unsigned)clr.z & 0xff) << 8) + ((unsigned)255 & 0xff));
}

float3		is_light(t_data *data, float3 lightdir, global t_lgt *lgt, float3 normale)
{
	short	index = data->id;
	float3	light_clr;

	lightdir = -normalize(lightdir);
	touch_object(data);
	light_clr = lgt->clr;
	if (data->id > -1 && index != data->id && data->objs[data->id].opacity < 1.0f)
	{
		data->ray_pos = data->intersect + data->ray_dir;
		calcul_light(&light_clr, &data->objs[data->id]);
		touch_object(data);
	}
	if (index == data->id)
	{
		data->nl++;
		return (calcul_clr(lightdir, normale, light_clr, &data->objs[index]));
	}
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
	return((float3)(light * cosinus * obj->clr));
}

float3		calcul_normale(t_data *data)
{
	float3	normale;
	float	k;
	float	m;


	if (data->objs[data->id].type == T_PLANE)
	{
		normale = -data->objs[data->id].rot;
	}
	else if (data->objs[data->id].type == T_SPHERE)
	{
		normale = data->intersect - data->objs[data->id].pos;
	}
	else if (data->objs[data->id].type == T_CYLINDER)
	{
		m = dot(data->ray_dir, data->objs[data->id].rot * data->t) +
			dot(data->objs[data->id].rot, data->off_set);
			normale = data->intersect - data->objs[data->id].pos -
			data->objs[data->id].rot * m;
	}
	else if (data->objs[data->id].type == T_CONE)
	{
		m = dot(data->ray_dir, data->objs[data->id].rot * data->t) +
			dot(data->objs[data->id].rot, data->off_set);
		k = tan((data->obj->radius / 2.0f) * (float)(M_PI / 180.0f));
		normale = data->intersect - data->objs[data->id].pos -
			(1.0f + k * k) * data->objs[data->id].rot * m;
	}
	return (fast_normalize(normale));
}
