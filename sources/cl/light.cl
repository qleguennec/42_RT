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
	data->safe--;
	if (data->objs[data->id].reflex > 0.0f && data->light_pow > 0.0f &&
		data->safe > 0)
		calcul_reflex_color(data);
	if (data->objs[data->id].opacity < 1.0f && data->light_pow > 0.0f &&
		data->safe > 0)
		clearness_color(data);
	data->rd_light += check_all_light(data);
	return(calcul_rendu_light(data));
}

float3		check_all_light(t_data *data)
{
	short	i = 0;
	float3	lightdir;
	float3	rd_light;

	rd_light = (float3){0.0f, 0.0f, 0.0f};
	while (i < data->n_lgts)
	{
		lightdir = data->intersect - data->lights[i].pos;
		rd_light += is_light(data, lightdir, &data->lights[i],
		calcul_normale(data));
		// PRINT3(rd_light, "rd_light");
		i++;
	}
	if (data->nl > 0)
	{
		return ((rd_light / (data->n_lgts + data->nl * data->ambiant)
			* data->objs[data->id].opacity * data->light_pow));
	}
	return (rd_light * data->objs[data->id].opacity);
}

float3		is_light(t_data *data, float3 lightdir, global t_lgt *lgt, float3 normale)
{
	short	index = data->id;
	float3	light_clr;
	float3	save_pos = data->ray_pos;
	float3	save_ray = data->ray_dir;
	float3	save_inter = data->intersect;

	lightdir = fast_normalize(lightdir);
	data->ray_pos = lgt->pos;
	data->ray_dir = lightdir;
	touch_object(data);
	if (index == data->id && fast_distance(data->intersect, lgt->pos) <
		fast_distance(data->intersect, lgt->pos) + PREC)
	{
		data->nl++;
		light_clr = calcul_clr(-lightdir, normale, lgt->clr,
			&data->objs[index]) + data->ambiant * data->objs[index].clr;
		// light_clr += is_shining(calcul_normale(data), -lightdir, 0.8f, 150.0f, lgt->clr);
		return (light_clr / (1.0f + data->ambiant));
	}
	data->ray_pos = save_pos;
	data->ray_dir = save_ray;
	data->intersect = save_inter;
	data->id = index;
	return (calcul_clr(data->ray_pos, -normale, data->ambiant,
		&data->objs[index]));
}
