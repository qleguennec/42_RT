#include "light.h"
#include "calc.h"

void	reflex_calcul(global t_obj *objs, global t_lgt *lights,
	short n_objs, short n_lights, float3 *ray_pos, float3 *ray_dir,
	float ambiant, short obj_ind, float *light_power, float3 *rd_light,
	short *safe)
{
	float	temp_power = *light_power;
	float3	temp_dir = *ray_dir;
	float3	temp_pos = *ray_pos;

	*light_power *= (1.0f - objs[obj_ind].reflex);
	clearness_color(objs, lights, n_objs, n_lights, ray_pos,
		ray_dir, safe, obj_ind, light_power, rd_light, ambiant);
	*light_power = temp_power - objs[obj_ind].reflex;
	calcul_reflex_ray(&temp_pos, &temp_dir, objs, obj_ind);
	get_color(objs, lights, n_objs, n_lights, ray_pos, ray_dir,
		obj_ind, light_power, rd_light, safe);
}

void	calcul_reflex_ray(float3 *ray_pos, float3 *ray_dir, global t_obj *objs,
	short obj_ind)
{
	float3 normale;

	normale = calcul_normale(&objs[obj_ind], ray_pos);
	*ray_dir = *ray_pos + (2 * normale * -my_dot(normale, *ray_pos));
}
