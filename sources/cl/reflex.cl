#include "light.h"
#include "calc.h"

void	calcul_reflex_color(t_data *data)
{
	short	id;
	float	temp_power;
	float3	temp_dir;
	float3	temp_pos;

	data->safe--;
	id = data->id;
	temp_power = data->light_pow;
	temp_dir = data->ray_dir;
	temp_pos = data->intersect;
	calcul_reflex_ray(data, &temp_pos, &temp_dir);
	touch_object(data);

	// get_lighting(data);
	// data->light_pow = temp_power * (1.0f - data->objs[id].reflex);
	// data->light_pow *= temp_power * (1.0f - data->objs[id].reflex);
	// data->id = id;
	// data->ray_dir = temp_dir;
	// data->intersect = temp_pos;
}

void	calcul_reflex_ray(t_data *data, float3 *ray_pos, float3 *ray_dir)
{
	float3 normale;

	normale = calcul_normale(data);
	data->ray_dir = data->ray_dir - (2.0f * normale * dot(normale, data->ray_dir));
	data->ray_pos = data->intersect - *ray_dir;
	data->light_pow *= data->objs[data->id].reflex;
}
