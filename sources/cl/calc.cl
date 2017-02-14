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

float		delta(float a, float b, float c)
{
	float	t0;
	float	t1;
	float	tmp;

	tmp = sqrt(b * b - (4 * a * c) / (2 * a));
	t0 = (-b + tmp);
	t1 = (-b - tmp);
	if (t1 > 0 && t1 < t0)
		return (t1);
	return (t0);
}


float	ray_norm(global t_obj *objs, float3 ray_pos, float3 ray_dir)
{
	if (objs->type == PLANE)
		return ((obj->t = ray_sphere_norm(objs, ray_pos, ray_dir)));
	else if (objs->type == CONE)
		return ((obj->t = ray_cone_norm(objs, ray_pos, ray_dir)));
	else if (objs->type == CYLINDER)
		return ((obj->t = ray_cylinder_norm(objs, ray_pos, ray_dir)));
	else if (objs->type == SPHERE)
		return ((obj->t = ray_sphere_norm(objs, ray_pos, ray_dir)));
	return (-1);
}

void	touch_object(t_obj *tab_objs, short nobjs, float3 ray_pos, float3 ray_dir, short *index, float *t)
{
	short	i;
	short	index;
	float	smallest_norm;
	float	norm;

	i = -1;
	index = -1;
	norm = -1;
	smallest_norm = -1;
	while(i++ <  nobjs)
	{
		obj = tab_objs[i];
		norm = ray_norm(obj, ray_pos, ray_dir);
		if (norm > 0 && (norm < small_dist || small_dist == -1))
		{
			smallest_norm = norm;
			index = i;
			*t = obj->t;
		}
	}
	return (index);
}

void calc(global t_obj *objs, short nobjs, global t_obj *lgts, short nblgts, float3 ray_pos)
{
    short	index;
    float	t;
	float3	intersect;

	printf("ok gros");
    index = touch_object(objs, nobjs, ray_pos, ray_dir, intersect, &t);
	intersect = ray_pos + ray_dir * t;
    get_lighting(objs, lgts, nobjs, nlgts, ambiant, intersect, ray_dir, index);
}
