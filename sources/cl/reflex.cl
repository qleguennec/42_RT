#include "light.h"
#include "calc.h"

void	reflex_calcul(t_data *data)
{
	float	temp_power = data->light_power;
	float3	temp_dir = data->ray_dir;
	float3	temp_pos = *ray_pos;

	data->light_pow *= (1.0f - data->objs[data->id].reflex);
	clearness_color(data);
	data->light_pow = temp_power * data->objs[data->id].reflex;
	calcul_reflex_ray(data, &temp_pos, &temp_dir);
	data->intersect = temp_pos;
	get_color(data);
}

void	calcul_reflex_ray(t_data * data, float3 *ray_pos, float3 *ray_dir)
{
	float3 normale;

	normale = calcul_normale(data->objs[data->id], ray_pos);
	data->ray_dir = *ray_pos + (2 * normale * -my_dot(normale, *ray_pos));
}
