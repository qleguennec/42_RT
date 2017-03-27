#include "light.h"
#include "calc.h"

void	reflex_calcul(t_data *data)
{
	short test;

	test = data->safe;
	data->safe++;
	float	temp_power = data->light_pow;
	float3	temp_dir = data->ray_dir;
	float3	temp_pos = data->intersect;
	short	id = data->id;

	data->light_pow *= (1.0f - data->objs[data->id].reflex);
	data->rd_light += check_all_light(data);
	data->light_pow = temp_power * data->objs[data->id].reflex;
	calcul_reflex_ray(data, &temp_pos, &temp_dir);
	// touch_object(data);
	while (test >= 0)
	{
		touch_object(data);
		// printf("light->pow = %f\n", data->light_pow);
		test--;
	}
	if (data->objs[(short)id].opacity < 1.0f && data->objs[(short)id].reflex < 1.0f)
	{
		data->option2 = 1;
		data->intersect = temp_pos;
		data->ray_dir = temp_dir;
		data->rd_light += check_all_light(data);
		clearness_color(data);
		data->safe = SAFE;
	}
	else
		data->rd_light = check_all_light(data);
}

void	calcul_reflex_ray(t_data * data, float3 *ray_pos, float3 *ray_dir)
{
	float3 normale;

	data->intersect = *ray_pos;
	// data->ray_pos = *ray_pos;
	normale = calcul_normale(data);
	data->ray_dir = *ray_pos - (2.0f * normale * dot(normale, *ray_pos));
	data->ray_pos = *ray_pos;
}
