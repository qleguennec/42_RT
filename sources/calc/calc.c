/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 17:50:51 by lgatibel          #+#    #+#             */
/*   Updated: 2017/02/10 16:45:41 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float		delta(float a, float b, float c)
{
	float	t0;
	float	t1;

	t0 = (-b + sqrt(b * b - (4 * a * c) / (2 * a));
	t1 = (-b - sqrt(b * b - (4 * a * c) / (2 * a));
	if (t1 > 0 && t1 < t0)
		return (t1);
	return (t0);
}


float	object_dist(global t_obj *objs, float3 ray_pos, float3 ray_dir)
{
	if (objs->type == PLANE)
		return (calc_sphere_dist(objs, ray_pos, ray_dir));
	else if (objs->type == CONE)
		return (calc_cone_dist(objs, ray_pos, ray_dir));
	else if (objs->type == CYLINDER)
		return (calc_cylinder_dist(objs, ray_pos, ray_dir));
	else if (objs->type == SPHERE)
		return (calc_sphere_dist(objs, ray_pos, ray_dir));
	return (-1);
}

void	touch_object(t_obj *objs, short nobjs, float3 ray_pos, float3 ray_dir, short *index, float *t)
{
	short	i;
	short	index;
	float	small_dist;
	float	tmp;

	i = -1;
	index = -1;
	small_dist = -1;
	while(i++ <  nobjs)
	{
		tmp = object_dist(objs, ray_pos, ray_dir);
		if (tmp > 0 && (tmp < small_dist || small_dist < 0))
		{
			index = i;
			closest
		}
		objs = objs->next;
	}
	*dist = small_dist;
	return (index);
}

void calc(global t_obj *objs, short nobjs, global t_obj *lgts, short nblgts, float3 ray_pos)
{
    short	index;
    float3	intesection;
	float	t;

    index = calc_obj_dist(objs, nobjs, ray_pos, ray_dir, &t);

    intersetion = ray_pos + ray_dir * t;

    get_lighting(objs, lgts, nobjs, nlgts, ambiant, ray_pos, ray_dir, index);
}
