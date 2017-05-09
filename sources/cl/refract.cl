
#include "light.h"

void clearness_color(t_data *data) 
{
	float	temp_power;

	short	temp_id;
	float3	temp_dir;
	float3	temp_pos;
	float3	temp_intersect;

	temp_id = data->id;
	temp_dir = data->ray_dir;
	temp_pos = data->ray_pos;
	temp_intersect = data->intersect;
	temp_power = data->light_pow;

	data->light_pow -= data->objs[data->id].opacity;
	data->light_obj_pow = data->objs[data->id].opacity;
	// // clearness_calcul(data);
	while (data->id == temp_id)
	{
		data->ray_pos = data->intersect + data->ray_dir;
		touch_object(data);
	}
	data->through = data->id;
	data->id = temp_id;
	data->ray_dir = temp_dir;
	data->ray_pos = temp_pos;
	data->intersect = temp_intersect;
	data->safe = 0;
	// data->power = temp_light_pow;
}

void	clearness_calcul(t_data *data)
{
	// short	index = data->id;

	// data->ray_dir = calcul_refract_ray(data, 1.0f, data->objs[data->id].refract);
	data->ray_pos = data->intersect + data->ray_dir;
	touch_object(data);
	// if (index == data->id)
	// {
	// 	data->ray_dir = calcul_refract_ray(data, data->objs[data->id].refract, 1.0f);
	// 	data->ray_pos = data->intersect + data->ray_dir * PREC;
	// 	touch_object(data);
	// }
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
