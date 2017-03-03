#include "light.h"
#include "lib.h"
#include "calc.h"

void	reflex_calcul(global t_obj *objs, global t_lgt *lights,
	short n_objs, short n_lights, float3 *ray_pos, float3 ray_dir,
	short obj_ind, float3 *light_power, float3 *rd_light)
{
	float temp_power = *light_power;
	float3 temp_dir = *ray_dir;

	*light_power *= (1.0 - objs[obj_ind]->reflex);
	*rd_light += clearness_color(lights, n_lights, objs, n_objs, obj_ind, ambiant,
		ray_dir, ray_pos, obj_ind, &light_power, &rd_light);
	*light_power = temp_power - objs[obj_ind]->reflex;
	 *ray_dir = calcul_reflex_ray();
	get_color(debug, *objs, *lights, n_objs, n_lights, ray_pos, ray_dir,
		obj_ind, light_power, rd_light);
}

void	calcul_reflex_ray(float3 *ray_pos, float3 *ray_dir, global t_obj *objs,
	short obj_ind)
{
	float3 normale;

	normale = calcul_normale(objs[obj_ind], *ray_pos);
	*ray_dir = *ray_pos + (2 * normale * -my_dot(normale, *ray_pos))
}
