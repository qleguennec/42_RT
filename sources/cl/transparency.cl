
#include "light.h"

void	clearness_color(global t_obj *objs, global t_lgt *lights,
	short n_objs, short n_lights, float3 ray_pos, float3 ray_dir,
	short obj_ind, float *light_power, float3 *rd_light)
{
	float3	new_pos = ray_pos;
	float3	rd_light = (float3){0.0f, 0.0f, 0.0f};

	*rd_light += check_all_light(lights, n_lights, objs, n_objs, obj_ind,
		ambiant, ray_dir, ray_pos)
	*light_power *= (objs[obj_ind].opacity);
	// ray_dir = calcul_reffract();
	if (objs[obj_ind].opacity < 1.0)
		rd_light += clearness_calcul(objs, lights, n_objs, n_lights, ray_pos,
			ray_dir, ray_dir, obj_ind, light_power, rd_light);
	if (light_power > 0.0f)
		get_color();
}

void	clearness_calcul(global t_obj *objs, global t_lgt *lights,
	short n_objs, short n_lights, float3 *new_pos, float3 ray_dir,
	short obj_ind, float *light_power, float3 *rd_light)
{
	short	index = obj_ind;

	while (index == obj_ind)
		new_pos = touch_object(objs, n_objs, new_pos, ray_dir, &index);
	if (index == -1)
	{
		*rd_light += (float3){0.0f, 0.0f, 0.0f} * light_power;
		*light_power = 0.0f;
	}
	else
	{
		obj_ind = index;
		*rd_light += (check_all_light(lights, n_lights, objs, n_objs, index,
			ambiant, ray_dir, new_pos) * light_power);
		*light_power *= (objs[obj_ind].opacity);
		// ray_dir = calcul_reffract();
	}
}

float3	calcul_refract_ray()
{

}
