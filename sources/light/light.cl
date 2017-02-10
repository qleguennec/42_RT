/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erodrigu <erodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 15:39:48 by erodrigu          #+#    #+#             */
/*   Updated: 2017/02/09 15:39:48 by erodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

include "light.h";
include "ray.h"

unsigned get_lighting(t_scene *scene, t_lionel pt)
{
	short	i = 0;
	float3	rd_light;
	float	size;
	float3	lightdir;

	rd_light.xyz = (scene->ambient, scene->ambient, scene->ambient);
	while (i < scene->n_lgts)
	{
		lightdir = normalize(pt->ray_pos - scene->b_lgts[i]->pos);
		rd_light += is_light(lightdir, scene->b_objs, scene->b_lgts,
		scene->n_lgts, scene->n_objs);
		i++;
	}
}

float3	is_light(float3 lightdir, t_obj *objs, t_obj *lights, short n_objs,
	short n_lights, short obj_indice)
{
	short	index;
	float	dist;

	dist = check(objs, n_objs, lightdir, &index);
}

float3	calcul_normale(t_obj *obj, float3 point, float3 rot)
{
	float3	normale;
	float3 pos_temp;

	if (obj->form == PLAN)
		normale = obj->rot;
	if (obj->form == SPHERE)
		normale = obj->pos - point;
	if (obj->form == CYLINDER)
	{
		pos_temp = (obj->pos.x, 0, obj.pos.z);
		normale = pos_temp - point;
		rotate_ray(normale, obj->rot);
	}
}
