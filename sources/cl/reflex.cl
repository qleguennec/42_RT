#include "light.h"
#include "calc.h"

void	check_intercept(t_data *data, short index, short light)
{
	short	id;
	float	temp_power;
	float3	temp_dir;
	float3	temp_pos;

	touch_object(data);
	id = data->id;
	temp_power = data->light_pow;
	temp_dir = data->ray_dir;
	temp_pos = data->intersect;
	if(light == 0 && data->objs[data->id].reflex > 0.0f)
	{
		if (data->objs[data->id].reflex != 1.0f)
		{
			data->light_pow *= (1.0f - data->objs[data->id].reflex);
			clearness_calcul(data);
		}
		data->light_pow = temp_power * data->objs[id].reflex;
		calcul_reflex_ray(data, &temp_pos, &temp_dir);
		touch_object(data);
	}
	if (data->id != index && data->objs[data->id].reflex > 0.0f && light)
	{
		calcul_reflex_ray(data, &temp_pos, &temp_dir);
		touch_object(data);
	}
}

void	calcul_reflex_ray(t_data *data, float3 *ray_pos, float3 *ray_dir)
{
	float3 normale;

	data->intersect = *ray_pos;
	normale = calcul_normale(data);
	data->ray_dir = *ray_pos - (2.0f * normale * dot(normale, *ray_pos));
	data->ray_pos = *ray_pos;
}
