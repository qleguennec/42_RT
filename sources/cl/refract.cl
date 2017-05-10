
#include "light.h"
static float3		transparancy_is_light(t_data *data, float3 lightdir, global t_lgt *lgt)
{
	float3	light_clr;
	float3	save_intersect;

	data->ray_pos = lgt->pos;
	data->ray_dir = lightdir;
	save_intersect = data->intersect;
	while (data->id == data->save_id)
	{
		touch_object(data);
		data->ray_pos = data->intersect + data->ray_dir;
	}
		// printf("test, id[%u], through[%u]\n", data->id, data->through);
	if ((data->id == data->through && fast_distance(save_intersect, lgt->pos) < 
	fast_distance(data->intersect, lgt->pos) + PREC))
	{
		data->nl++;
		light_clr = calcul_clr(-lightdir, data->normale, lgt->clr * (data->objs[data->id].clr));
		light_clr += is_shining(data->normale, -lightdir, lgt->clr);
		return (light_clr);
	} 
	if (fast_distance(save_intersect, data->save_pos) < 
	fast_distance(data->intersect, data->save_pos)+ PREC)
		data->test++;
	return (0);
}

static float3		transparancy_check_all_light(t_data *data)
{
	short	i;
	float3	lightdir;
	float3	rd_light;
	float3	clr;

	i = -1;
	rd_light = 0.0f;
	clr = data->objs[data->id].clr;
	while (++i < data->n_lgts)
	{
		lightdir = fast_normalize(data->intersect - data->lights[i].pos);
		rd_light += transparancy_is_light(data, lightdir, &data->lights[i]);
	}
	// rd_light += data->ambiant * clr;// a surement retirer
			rd_light += calcul_clr(data->save_dir, -data->normale, data->ambiant * data->save_clr);

	if (!data->nl)
	 	return (rd_light * data->light_obj_pow);
	else if (data->n_lgts == 1)
		return (rd_light / (1.0f + data->ambiant) * data->light_obj_pow);
	return (rd_light  / (data->n_lgts - data->test + data->ambiant) * data->light_obj_pow);
}

void 	clearness_color(t_data *data) 
{
	data->light_obj_pow = data->light_pow - data->objs[data->id].opacity;
	data->light_pow -= data->light_obj_pow;
	if (data->light_obj_pow <= 0.0f)
		return ;
	while (data->id == data->save_id)
	{
		data->ray_pos = data->intersect + data->ray_dir;
		touch_object(data);
	}
	if (data->id > -1)
	{
		data->through = data->id;
		data->rd_light += transparancy_check_all_light(data);
		data->test = 0;
	}
}

float3	calcul_refract_ray(t_data *data, float refract1, float refract2)
{
	float	n;
	float	cosi;
	float	c1;
	float	c2;
	float3	normale;

	normale = calcul_normale(data);
	cosi = -dot(normale, data->ray_dir);
	n = refract1 / refract2;
	c1 = n * n * (1.0f - cosi * cosi);
	if (c1 > 1.0f)
		return (data->ray_dir);
	c2 = sqrt(1.0f - c1);
	return (data->ray_dir + (n * cosi - c2) * normale);
}

// void	clearness_calcul(t_data *data)
// {
// 	// short	index = data->id;

// 	// data->ray_dir = calcul_refract_ray(data, 1.0f, data->objs[data->id].refract);
// 	data->ray_pos = data->intersect + data->ray_dir;
// 	touch_object(data);
// 	// if (index == data->id)
// 	// {
// 	// 	data->ray_dir = calcul_refract_ray(data, data->objs[data->id].refract, 1.0f);
// 	// 	data->ray_pos = data->intersect + data->ray_dir * PREC;
// 	// 	touch_object(data);
// 	// }
// }