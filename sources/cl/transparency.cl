
#include "light.h"

void clearness_color(t_data *data)
{
	short	id;
	float	temp_power;
	float3	temp_dir;
	float3	temp_pos;

	id = data->id;
	temp_power = data->light_pow;
	temp_dir = data->ray_dir;
	temp_pos = data->intersect;
	clearness_calcul(data);
	touch_object(data);
	get_lighting(data);
	data->id = id;
	data->light_pow = temp_power - data->objs[id].opacity;
	data->ray_dir = temp_dir;
	data->intersect = temp_pos;

}

void	clearness_calcul(t_data *data)
{
	short	index = data->id;

	data->ray_dir = calcul_refract_ray(data, 1.0f, data->objs[data->id].refract);
	data->ray_pos = data->intersect + data->ray_dir * PREC;
	touch_object(data);
	if (index == data->id)
	{
		data->ray_dir = calcul_refract_ray(data, data->objs[data->id].refract, 1.0f);
		data->ray_pos = data->intersect + data->ray_dir * PREC;
		touch_object(data);
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
