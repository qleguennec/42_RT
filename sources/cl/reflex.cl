#include "light.h"
#include "calc.h"

void	reflex_calcul(t_data *data)
{
	data->safe--;
	float	temp_power = data->light_pow;
	float3	temp_dir = data->ray_dir;
	float3	temp_pos = data->intersect;
	short	id = data->id;

	data->light_pow *= (1.0f - data->objs[id].reflex);
	// printf("light power 1 = %f\n", data->light_pow);
	if (data->objs[(short)id].reflex < 1.0f)
	{
		// data->rd_light += check_all_light(data);
		clearness_color(data);
	}
	data->light_pow = temp_power * data->objs[id].reflex;
	// printf("light power 2 = %f\n", data->light_pow);
	calcul_reflex_ray(data, &temp_pos, &temp_dir);
	touch_object(data);
}

void	calcul_reflex_ray(t_data * data, float3 *ray_pos, float3 *ray_dir)
{
	float3 normale;

	data->intersect = *ray_pos;
	normale = calcul_normale(data);
	data->ray_dir = *ray_pos - (2.0f * normale * dot(normale, *ray_pos));
	data->ray_pos = *ray_pos;
}
