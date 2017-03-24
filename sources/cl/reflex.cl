#include "light.h"
#include "calc.h"

void	reflex_calcul(t_data *data)
{
	float	temp_power = data->light_pow;
	float3	temp_dir = data->ray_dir;
	float3	temp_pos = data->intersect;

	data->light_pow *= (1.0f - data->objs[data->id].reflex);
	// clearness_color(data);
	data->safe++;
	data->rd_light += check_all_light(data);
	data->light_pow *=  (1.0f - data->objs[data->id].opacity);

	data->light_pow = temp_power * data->objs[data->id].reflex;
	calcul_reflex_ray(data, &temp_pos, &temp_dir);


	touch_object(data);
	if (data->safe < SAFE)
	{
		data->rd_light += check_all_light(data);
		data->light_pow *=  ( data->objs[data->id].opacity);
		// data->light_pow -=  (1 - data->objs[data->id].opacity);
		// printf("light->power = %f\n", data->light_pow);
	}	

	// clearness_color(data);

	// data->ray_dir = temp_dir;
	// data->intersect = temp_pos;
	// data->light_pow = temp_power;
	
	// get_color(data);
}

void	calcul_reflex_ray(t_data * data, float3 *ray_pos, float3 *ray_dir)
{
	float3 normale;

	data->intersect = *ray_pos;

	data->ray_pos = *ray_pos;

	normale = calcul_normale(data);
	data->ray_dir = *ray_pos - (2.0f * normale * dot(normale, *ray_pos));
	data->ray_pos = *ray_pos;
}
