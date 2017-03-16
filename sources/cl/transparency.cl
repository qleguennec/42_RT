
#include "light.h"

void	clearness_color(t_data *data)
{
	data->rd_light += check_all_light(data);
	data->light_pow *= objs[data->id].opacity;
	if (objs[data->id].opacity < 1.0f)
		clearness_calcul(data);
	if (data->light_pow > 0.0f)
		get_color(data);
}

//fonction a amelioré, (calcul des different indices si on passe pas dans l'air)
void	clearness_calcul(t_data *data)

{
	short	index = data->id;

	// *ray_dir = calcul_refract_ray(data, 1.0f, data->objs[data->id].refract);
	data->intersect = touch_object(data);
	if (index == data->id)
	{
		// *ray_dir = calcul_refract_ray(data, data->objs[data->id].refract, 1.0f);
		data->intersect = touch_object(data);
	}
	if (index == -1)
	{
		// data->rd_light += (float3){0.0f, 0.0f, 0.0f} * light_power;
		data->light_pow = 0.0f;
	}
		data->rd_light += (check_all_light(data) * data->light_pow);
		data->light_pow -= (objs[data->id].opacity);
		// *ray_dir = calcul_refract_ray(data, data->objs[data->id].refract, 1.0f);
}

float3	calcul_refract_ray(t_data *data, float refract1, float refract2)
{
	float	n;
	float	c1;
	float	c2;
	float3	normale;

	normale = calcul_normale(obj, data->intersect);
	n = refract1 / refract2;
	return (data->ray_dir * n + normale * (n * c1 - c2));
}
