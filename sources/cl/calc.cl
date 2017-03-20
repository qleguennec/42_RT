/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 17:50:51 by lgatibel          #+#    #+#             */
/*   Updated: 2017/02/13 11:10:55 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj_def.h"
#include "calc.h"
#include "light.h"
#include "light.cl"
#include "calc_intersect.cl"
#include "rotate.cl"
//debug
#define COLOR 0
//
float		calc_delta(float a, float b, float c)
{
	float	t0;
	float	t1;
	float	tmp;

	tmp = (b * b) - (4.0f * a * c);
	if(tmp < 0.0f)
		return (-1);
	tmp = sqrt(tmp);
	t0 = ((-b + tmp) / (2.0f * a));
	t1 = ((-b - tmp) / (2.0f * a));
	if (t0 < t1)
		return (t0);
	return (t1);
}


static short	ray_intersection(t_data *data, global t_obj *obj)
{
	if (obj->type == T_PLANE)
		return (plane_intersection(data, obj));
	else if (obj->type == T_CONE)
		return (cone_intersection(data, obj));
	else if (obj->type == T_CYLINDER)
		return (cylinder_intersection(data, obj));
	else if (obj->type == T_SPHERE)
		return (sphere_intersection(data, obj));
	return (0);
}

void			touch_object(t_data *data)
{
	short			i;
	float			smallest_norm;
	float			norm;
	float3			closest_intersect;

	i = -1;
	data->id = -1;
	smallest_norm = -1;
//			if (obj->type == T_PLANE && dot(tmp_intersect - obj->pos, tmp_intersect - obj->pos) < obj->radius * obj->radius) // formule du disque
	while(++i <  data->n_objs)
	{
		if (ray_intersection(data, &data->objs[i]))
			if ((norm = fast_distance(data->intersect,data->ray_pos)) > 0.0f &&
				(norm < smallest_norm || smallest_norm == -1))
			{
				closest_intersect = data->intersect;
				smallest_norm = norm;
				data->id = i;
			}
	}
	data->intersect = closest_intersect;
}

static void		init_data(t_data *data, global t_obj *objs,
global t_lgt *lgts, short n_objs, short n_lgts, float3 ray_pos,
float3 ray_dir, float ambiant, float3 intersect,
global unsigned int *pixel)
{
	data->objs = objs;
	data->lights = lgts;
	data->n_objs = n_objs;
	data->n_lgts = n_lgts;
	data->ray_pos = ray_pos;
	data->ray_dir = ray_dir;
	data->ambiant = ambiant;
	data->id = -1;
	data->intersect = intersect;
	data->pixel = pixel;
	data->safe = 0;
	data->light_pow = 1.0f;
	data->rd_light = 0.0f;
}

void calc_picture(int debug, global unsigned int *pixel, global t_obj *objs,
	global t_lgt *lgts, short n_objs, short n_lgts, float3 ray_pos,
	float3 ray_dir, global t_cam *cam, short x, short y)
{
	t_data	data;
	float3	intersect;
	float	ambiant = 0.20;

	init_data(&data, objs, lgts, n_objs, n_lgts, ray_pos, ray_dir,
			ambiant, intersect, pixel);
	if (debug)
	{
	/*
		float3 t;
		float3 t2;
		float t3;
		t = (float3){2, 3, 4};
		t2 = (float3){5, 6, 7};
		t3 = dot(t.x, t2.x);
		printf("t3 = [%f]\n",t3);
		printf("type de lobjet %u\n", tab_objs[0].type);
		PRINT3(ray_dir,"ray_dir");
		printf("x[%u] et y[%u]\n",x,y);
	*/
	}
    touch_object(&data);
	if (data.id > -1 && COLOR)
	{
		if (data.id == 0)
			*(data.pixel) = 0xff0000FF;
		else if (data.id == 1)
			*pixel = 0x00ff00FF;
		else if (data.id == 2)
			*pixel = 0x00ffffFF;
		else if (data.id == 3)
			*pixel = 0xffffffFF;
		else if (data.id == 4)
			*pixel = 0xffff00FF;
		else
			*pixel = 0xff00ffFF;

	}
	else if (data.id > -1 && !COLOR)
	{
		*pixel = get_lighting(&data);
	}
	else
		*pixel = 0xFFFFFFFF;
}
