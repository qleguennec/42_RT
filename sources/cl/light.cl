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
#include "shiness.cl"
#include "light.h"

unsigned	get_lighting(t_data *data)
{
	get_color(data);
	return(calcul_rendu_light(data));
}

void	init_laputain_desamere(t_data *data)
{
	// data->objs[0].reflex = 1.0f;
	// data->objs[1].reflex = 1.0f;
	// data->objs[2].reflex = 1.0f;
	// data->objs[3].reflex = 1.0f;
	// data->objs[4].reflex = 1.0f;
	// data->objs[4].refract = 1.3f;
	// data->objs[5].reflex = 1.0f;
	// data->objs[6].reflex = 1.0f;
}

void	get_color(t_data *data)
{
	while (data->safe > 0 && data->light_pow > 0.0f)
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
		lightdir = data->intersect - data->lights[i].pos;
		rd_light += is_light(data, lightdir, &data->lights[i],
		calcul_normale(data));
		i++;
	}
	printf("nl = %d\n", data->nl);
	if (data->nl > 0)
	{
		return ((rd_light / (data->nl + data->n_lgts * data->ambiant)
			* data->objs[data->id].opacity * data->light_pow));
	}
	return (rd_light * data->objs[data->id].opacity);
}

unsigned	calcul_rendu_light(t_data *data)
{
	float3	clr;

	if (data->rd_light.x > 1.0f)
		data->rd_light.x = 1.0f;
	if (data->rd_light.y > 1.0f)
		data->rd_light.y = 1.0f;
	if (data->rd_light.z > 1.0f)
		data->rd_light.z = 1.0f;
	clr =  data->rd_light * 255.0f;
	return ((((unsigned)clr.x & 0xff) << 24) + (((unsigned)clr.y & 0xff) << 16)
		+ (((unsigned)clr.z & 0xff) << 8) + ((unsigned)255 & 0xff));
}

float3		is_light(t_data *data, float3 lightdir, global t_lgt *lgt, float3 normale)
{
	short	index = data->id;
	float3	light_clr;
	float3	save_pos = data->ray_pos;
	float3	save_ray = data->ray_dir;
	float3	save_inter = data->intersect;

	lightdir = normalize(lightdir);
	data->ray_pos = lgt->pos;
	data->ray_dir = lightdir;
	check_intercept(data, index, 1);
	// light_clr = lgt->clr;
	// if (data->id != -1 && index != data->id && data->objs[data->id].opacity < 1.0f)
	// {
		// data->ray_pos = data->intersect;
		// data->ray_dir = lightdir;

		// calcul_light(&light_clr, &data->objs[data->id]);
		// check_intercept(data, 1);
	// }
	if (index == data->id && fast_distance(save_inter, lgt->pos) <=
		fast_distance(data->intersect, lgt->pos) + PREC)
	{
		data->nl++;
		light_clr = calcul_clr(-lightdir, normale, lgt->clr,
			&data->objs[index]) + data->ambiant * data->objs[index].clr;
		light_clr += is_shining(calcul_normale(data), -lightdir, 0.8f, 150.0f, lgt->clr);
		return (light_clr / (1.0f + data->ambiant));
	}
	data->ray_pos = save_pos;
	data->ray_dir = save_ray;
	data->intersect = save_inter;
	data->id = index;
	// return (data->ambiant * data->objs[index].clr);
	return (calcul_clr(data->ray_pos, normale, data->ambiant,
		&data->objs[index]));

	// return ((float3){0.0f, 0.0omf, 0.0f});
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

	ray = fast_normalize(ray);
	normale = fast_normalize(normale);
	cosinus = dot(ray, normale);
	if (cosinus < 0.0)
		cosinus = -cosinus;
	return((float3)(light * cosinus * obj->clr));
}

float3		calcul_normale(t_data *data)
{
	float3	normale;
	float	k;
	float	m;

	if (data->objs[data->id].type == T_PLANE)
	{
		if (dot(data->ray_dir, data->objs[data->id].rot) > 0)
			normale = data->objs[data->id].rot;
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
