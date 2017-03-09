
#include "light.h"

void	clearness_color(global t_obj *objs, global t_lgt *lights,
	short n_objs, short n_lights, float3 *ray_pos, float3 *ray_dir, short *safe,
	short obj_ind, float *light_power, float3 *rd_light, float ambiant)
{
	float3	new_pos = *ray_pos;

	*rd_light += check_all_light(lights, n_lights, objs, n_objs, obj_ind,
		ambiant, ray_dir, ray_pos)
	*light_power *= objs[obj_ind].opacity;
	if (objs[obj_ind].opacity < 1.0f)
		rd_light += clearness_calcul(objs, lights, n_objs, n_lights, ray_pos,
			ray_dir, safe, obj_ind, light_power, rd_light, ambiant);
	if (*light_power > 0.0f)
		get_color(objs, lights, n_objs, n_lights, ray_pos, ray_dir, obj_ind,
			light_power, rd_light, safe, ambiant);
}

void	clearness_calcul(global t_obj *objs, global t_lgt *lights,
	short n_objs, short n_lights, float3 *new_pos, float3 *ray_dir, short *safe,
	short obj_ind, float *light_power, float3 *rd_light, float ambiant)

{
	short	index = obj_ind;

	ray_dir = calcul_refract_ray(ray_dir, new_pos, &objs[obj_ind], 1,
		objs[obj_ind].refract);
	new_pos = touch_object(objs, n_objs, *new_pos, *ray_dir, &index);
	if (index == -1)
	{
		// *rd_light += (float3){0.0f, 0.0f, 0.0f} * light_power;
		*light_power = 0.0f;
	}
	if (index == obj_ind)
	{
		ray_dir = calcul_refract_ray(ray_dir, new_pos, &objs[obj_ind],
			objs[obj_ind].refract, 1);
		new_pos = touch_object(objs, n_objs, *new_pos, *ray_dir, &index);
	}
	else
	{
		obj_ind = index;
		*rd_light += (check_all_light(lights, n_lights, objs, n_objs, index,
			ambiant, ray_dir, new_pos) * light_power);
		*light_power *= (objs[obj_ind].opacity);
		ray_dir = calcul_refract_ray(ray_dir, new_pos, &objs[obj_ind],
			objs[obj_ind].refract, 1);
	}
}

float3	calcul_refract_ray(float3 *ray_dir, float3 *ray_pos, global t_obj *obj,
	float refract1, float refract2)
{
	float	n;
	float	c1;
	float	c2;
	float3	normale;

	normale = calcul_normale(obj, ray_pos);
	n = refract1 / refract2;
	c1 = my_dot(normale, *ray_dir);
	c2 = sqrt(1 - n * n + n * n * c1 * c1);
	return (*ray_dir * n + normale * (n * c1 - c2));
}
