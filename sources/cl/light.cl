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
	// short	id;
	// float3	temp_dir;
	// float3	temp_pos;

	// data->safe--;
	data->safe = 1;
	// id = data->id;
	// temp_dir = data->ray_dir;
	// temp_pos = data->intersect;
	while (data->safe > 0 && data->light_pow > 0.0f)
	{

		if (data->objs[data->id].reflex > 0.0f)
		{
			calcul_reflex_color(data);
		}
		else if (data->objs[data->id].opacity < 1.0f)
		{
			break ;// WIP
		}
		else
			break ;
	}
	data->rd_light = check_all_light(data);
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
	if (data->nl >0)
	{
		return ((rd_light / (data->nl + data->nl * data->ambiant)
			* data->objs[data->id].opacity * data->light_pow) * data->objs[data->id].clr);
		// 	return ((rd_light
			// * data->objs[data->id].opacity * data->light_pow));
	}
	return (rd_light * data->objs[data->id].opacity * data->objs[data->id].clr);
}

float3		is_light(t_data *data, float3 lightdir, global t_lgt *lgt, float3 normale)
{
	short	index = data->id;
	float3	light_clr;
	float3	save_intersect = data->intersect;
	// float3	save_pos = data->ray_pos;
	// float3	save_dir = data->ray_dir;

	lightdir = fast_normalize(lightdir);
	data->ray_pos = lgt->pos;
	data->ray_dir = lightdir;
	touch_object(data);
	if (index == data->id && fast_distance(save_intersect, lgt->pos) <
		fast_distance(data->intersect, lgt->pos) + PREC)
	{
		data->nl++;
		light_clr = calcul_clr(-lightdir, normale, lgt->clr,
			&data->objs[index]) + data->ambiant;
		// light_clr += is_shining(calcul_normale(data), -lightdir, 0.8f, 150.0f, lgt->clr);
		data->id = index;
		return (light_clr / (1.0f + data->ambiant));
	}
		data->id = index;
	return (calcul_clr(data->ray_pos, -normale, data->ambiant,
	&data->objs[index]));//* data->objs[data->id].clr);
	// return (data->objs[index].clr * data->ambiant);
}
