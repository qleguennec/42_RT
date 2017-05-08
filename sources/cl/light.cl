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
#include "noise.h"
#include "noise.cl"

unsigned	get_lighting(t_data *data)
{
	float3 color  = (float3){202.0f, 164.0f, 10.0f};
	// temp_pos = data->intersect;
	// data->safe = 1;
	// while (data->safe-- > 0 && data->light_pow > 0.0f)
	// {
	// 	if (data->objs[data->id].reflex > 0.0f)
	// 	{
	// 		calcul_reflex_color(data);
	// 	}
	// 	else if (data->objs[data->id].opacity < 1.0f) // a changer en if
	// 	{
	// 		break ;// WIP
	// 	}
	// 	else
	// 		break ;
	// }
	// data->save_dir = data->ray_dir;
	// data->save_pos = data->ray_pos;
	data->save_clr = twocolor_lerp(data->objs[data->id].clr,
		color / 255.0f, (float)smooth_noise_3d(data->intersect));
	// data->save_inter = data->inter;
	// data->save_inter = data->intersect;
	// data->save_id = data->id;
	data->rd_light = check_all_light(data);
	return(calcul_rendu_light(data));
}

float3		check_all_light(t_data *data)
{
	short	i;
	float3	lightdir;
	float3	rd_light;
	float3	normale;

	i = -1;
	rd_light = 0.0f;
	rd_light = 0.0f;
	normale = calcul_normale(data);
	while (++i < data->n_lgts)
	{
		lightdir = fast_normalize(data->save_inter - data->lights[i].pos);
		rd_light += is_light(data, lightdir, &data->lights[i], normale);
	}
	rd_light += calcul_clr(data->save_dir, -normale, data->ambiant * data->save_clr)
	* data->objs[data->id].opacity * data->light_pow;
	if (!data->nl)
	 	return (rd_light);
	else if (data->n_lgts == 1)
		return (rd_light + (rd_light * (data->nl / 20.0f)) / data->n_lgts);
	return ((rd_light + ((rd_light * data->nl) / 20.0f)) / (data->n_lgts - data->test));
}

float3		is_light(t_data *data, float3 lightdir, global t_lgt *lgt, float3 normale)
{
	float3	light_clr;

	data->ray_pos = lgt->pos;
	data->ray_dir = lightdir;
	touch_object(data);
	if (data->id == data ->save_id && fast_distance(data->save_inter, lgt->pos) <
		fast_distance(data->intersect, lgt->pos) + PREC)
	{
		data->nl++;
		light_clr = calcul_clr(-lightdir, normale, lgt->clr * data->save_clr);
		// light_clr += is_shining(calcul_normale(data), -lightdir, 0.8f, 150.0f, data->save_clr);
		return (light_clr );
	}
	if (fast_distance(data->save_inter, data->save_pos) <
	fast_distance(data->intersect, data->save_pos)+ PREC)
		data->test++;
	return (0);
}
