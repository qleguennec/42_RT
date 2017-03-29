#include "light.h"
#include "calc.h"

void	check_intercept(t_data *data, short light)
{
	short	id = data->id;
	float	temp_power = data->light_pow;
	float3	temp_dir = data->ray_dir;
	float3	temp_pos = data->intersect;

	touch_object(data);
	if(data->obj[data->id].reflex > 0.0f && !light)
	{
		data->light_pow *= (1.0f - data->objs[data->id].reflex);
		clearness_calcul(data);
		data->light_pow = temp_power * data->objs[id].reflex;
		calcul_reflex_ray(data, &temp_pos, &temp_dir);
		touch_object(data);
	}
	else if(data->obj[data->id].reflex > 0.0f && light)
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
