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
#include "refract.cl"
#include "shiness.cl"
#include "light.h"
#include "color.cl"


unsigned	get_lighting(t_data *data)
{
	short	opacity;
	// short	save_id = data->id;
	// float3	save_dir = data->ray_dir;
	// float3	save_pos = data->ray_pos;
	// float3	save_intersect = data->intersect;
	// float3	save_clr = data->save_clr;
	save(data);
	opacity = 0;
	while (data->reflex < MAX_REFLECTION && opacity < MAX_TRANSPARANCY > 0 &&
	 data->light_pow > 0.0f)
	{
		if (opacity < MAX_TRANSPARANCY &&
			data->objs[data->id].opacity < 1.0f && REFLEX < 1.0f)
		{
			clearness_color(data);
			load(data);
			opacity++;
		}
		if (data->reflex < MAX_REFLECTION && REFLEX > 0.0f)
			calcul_reflex_ray(data);
		else
			break ;
	}
	// return(calcul_rendu_light(data));
	
		// data->save_id = save_id;
		// data->save_dir = save_dir;
		// data->save_pos = save_pos;
		// data->save_inter = save_intersect;
		// data->save_clr = save_clr;
		// data->save_t
		// save(data);
		// load(data);
		data->normale = calcul_normale(data);
		data->rd_light += check_all_light(data);
	return(calcul_rendu_light(data));
}

float3		check_all_light(t_data *data)
{
	short	i;
	float3	lightdir;
	float3	rd_light;

	i = -1;
	rd_light = 0.0f;
	data->nl = 0;
	data->test = 0;
	while (++i < data->n_lgts)
	{
		lightdir = fast_normalize(data->save_inter - data->lights[i].pos);
		rd_light += is_light(data, lightdir, &data->lights[i]);
	}
	if (data->light_pow <= 0.0f)
	{
		 rd_light = calcul_clr(data->save_dir, -data->normale,
		 AMBIANT * rd_light);
		 data->light_pow = .20f;
	}
	else
		rd_light += calcul_clr(data->save_dir, -data->normale,
		 AMBIANT * data->save_clr);

	if (!data->nl || data->test >= data->n_lgts)
	 	return (rd_light);
	else if (data->n_lgts == 1 || (data->n_lgts - data->test == 1))
		return ((rd_light / (1.0f + AMBIANT)) * data->light_pow);
	return (rd_light / (data->n_lgts - data->test + AMBIANT) *
	 data->light_pow);
}

float3		is_light(t_data *data, float3 lightdir, global t_lgt *lgt)
{
	float3	light_clr;

	data->ray_pos = lgt->pos;
	data->ray_dir = lightdir;
	touch_object(data);
	if ((data->id == data ->save_id &&
		fast_distance(data->save_inter, lgt->pos) <
		fast_distance(data->intersect, lgt->pos) + PREC))
	{
		data->nl++;
		light_clr = calcul_clr(-lightdir, data->normale,
			lgt->clr * data->save_clr);
		if (data->objs[data->save_id].specular != 0.0f)
			light_clr += is_shining(data->normale, -lightdir, lgt->clr);
		return (light_clr);
	}
	if (fast_distance(data->save_inter, data->save_pos) + PREC <
	fast_distance(data->intersect, data->save_pos) &&
	 dot(data->ray_dir,	data->save_dir) + PREC2 < 0.0f)
		data->test++;
	return (0);
}
