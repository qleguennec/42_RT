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
#include "calc_normal.cl"
#include "init.cl"

float		calc_delta(float3 *disc)
{
	float	t0;
	float	t1;
	float	tmp;

	tmp = (disc->y * disc->y) - (4.0f * disc->x * disc->z);
	if(tmp < 0.0f)
		return (-1);
	tmp = sqrt(tmp);
	t0 = ((-disc->y + tmp) / (2.0f * disc->x));
	t1 = ((-disc->y - tmp) / (2.0f * disc->x));
	if (t0 < t1)
		return (t0);
	return (t1);
}

static short	ray_intersection(t_data *data, short *index)
{
	if (data->objs[(int)*index].type == T_PLANE)
		return (plane_intersection(data, index));
	else if (data->objs[(int)*index].type == T_CONE)
		return (cone_intersection(data, index));
	else if (data->objs[(int)*index].type == T_CYLINDER)
		return (cylinder_intersection(data, index));
	else if (data->objs[(int)*index].type == T_SPHERE)
		return (sphere_intersection(data, index));
	//else if (data->objs[(int)*index].type == T_DISK)
	// 	return (disk_intersection(data));
	return (0);
}

void			touch_object(t_data *data)
{
	short			index;
	float			smallest_norm;
	float			norm;
	float3			closest_intersect;

	float	t;
	t = -1;

	index = -1;
	data->id = -1;
	smallest_norm = -1;
	while(++index < data->n_objs)
	{
		if (ray_intersection(data, &index))
			if ((norm = fast_distance(data->intersect, data->ray_pos)) > 0.0f &&
				(norm < smallest_norm || smallest_norm == -1))
			{
				closest_intersect = data->intersect;
				smallest_norm = norm;
				data->id = index;
				t = data->t;
			}
	}
	data->intersect = closest_intersect;
	data->t = t;
	if (!data->is_light)
	{
		data->inter = data->intersect;
		data->is_light = 1;
	}
}



void calc_picture(int debug, global unsigned int *pixel, global t_obj *objs,
	global t_lgt *lgts, short n_objs, short n_lgts, float3 ray_pos,
	float3 ray_dir, global t_cam *cam, short x, short y)
{
	t_data	data;
	float	ambiant = 0.20f; // a setter par benj par la suite
	init_data(&data, objs, lgts, n_objs, n_lgts, ray_pos, ray_dir, ambiant,
     pixel);
	touch_object(&data);
	if (!COLOR && data.id > -1)
	{
		if (data.id == 0 ){*pixel = 0x00ff00FF;}
		else if (data.id == 1){*pixel = 0xff0000FF;}
		else if (data.id == 2){*pixel = 0x00ffffFF;}
		else if (data.id == 3){*pixel = 0xffffffFF;}
		else if (data.id == 4){*pixel = 0xffff00FF;}
		else{*pixel = 0xff00ffFF;}
	}
	else if (COLOR && data.id > -1)
		*pixel = get_lighting(&data);
	else
		*pixel = FONT;
}
