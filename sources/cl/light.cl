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
	data->safe--;
	if (data->objs[data->id].reflex > 0.0f && data->light_pow > 0.0f &&
		data->safe > 0)
		calcul_reflex_color(data);
	if (data->objs[data->id].opacity < 1.0f && data->light_pow > 0.0f &&
		data->safe > 0)
		clearness_color(data);
	if (data->objs[data->id].reflex != 1.0f)
		data->rd_light += check_all_light(data);
	return(calcul_rendu_light(data));
}



void	init_laputain_desamere(t_data *data)
{
	// data->objs[0].reflex = 1.0f;
	data->objs[0].type = T_PYRAMID;
	// data->objs[1].reflex = 1.0f;
	// data->objs[2].reflex = 1.0f;
	// data->objs[3].reflex = 1.0f;
	// data->objs[4].reflex = 1.0f;
	// data->objs[4].refract = 1.55f;
	// data->objs[5].reflex = 1.0f;
	// data->objs[6].reflex = 1.0f;
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
		return ((rd_light / (data->n_lgts + data->nl * data->ambiant)
			* data->objs[data->id].opacity * data->light_pow));
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
	touch_object(data);
	if (index == data->id && fast_distance(data->intersect, save_pos) <
		fast_distance(save_inter, save_pos) + PREC)
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
	return (calcul_clr(data->ray_pos, -normale, data->ambiant,
		&data->objs[index]));
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
	if (cosinus < 0.0f)
		return((float3){0.0f, 0.0f, 0.0f});
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
		float3 	rot;
		data->option = 2;
		rot = rotate_ray(&data->rot, data, &data->id);

		m = dot(data->ray_dir, rot) * data->t +
			dot(rot, data->offset);

		normale = data->intersect - data->objs[data->id].pos -
			rot * m;
		// normale  = rotate_ray(&normale, data, &data->id);
	}
	else if (data->objs[data->id].type == T_CONE)
	{
		m = dot(data->ray_dir, data->objs[data->id].rot) * data->t +
			dot(data->objs[data->id].rot, data->off_set);
		k = tan((data->obj->radius / 2.0f) * (float)(M_PI / 180.0f));
		normale = data->intersect - data->objs[data->id].pos -
			(1.0f + k * k) * data->objs[data->id].rot * m;
	}
	else if	(data->objs[data->id].type == T_TORUS)
		calcul_normal_egg(data, &normale);
	else if (data->objs[data->id].type == T_PYRAMID)
		calcul_normal_paraboloid(data, &normale);
	return (fast_normalize(normale));
}

void    calcul_normal_egg(t_data *data, float3 *normale)
{
    float3    m;
    float3    k;
    float    a;
    float    b;
    float    k1;
    float    k2;
    float    sr;

    data->rdir = rotate_ray(&data->ray_dir, data, &data->id);
    sr = pow(data->objs[data->id].radius, 2.0f);
    data->rdir = rotate_ray(&data->ray_dir, data, &data->id);
    k1 = 2.0f * data->objs[data->id].height * (dot(data->rdir, data->rot));
    k2 = sr + 2.0f * data->objs[data->id].height *
            dot(data->offset, data->rdir) - data->objs[data->id].height;
    a = 4.0f * sr * dot(data->rdir, data->rdir) - k1 * k1;
    b = 2.0f * (4.0f * sr *    dot(data->rdir, data->offset) - k1 * k2);
    m = data->objs[data->id].pos + data->rdir * data->objs[data->id].height / 2.0f;
    k = data->intersect - m;
    *normale = data->objs[data->id].radius - data->rdir * (1.0f - pow(b, 2.0f) /
                pow(a, 2.0f) * dot(k, data->rdir));
}

void    calcul_normal_paraboloid(t_data *data, float3 *normale)
{
    float    m;

    m = dot(data->ray_dir, data->rot) * data->t +
        dot(data->rot, data->offset);
    data->rdir = rotate_ray(&data->ray_dir, data, &data->id);
    *normale = data->intersect - data->objs[data->id].pos - data->rdir * m;
}
