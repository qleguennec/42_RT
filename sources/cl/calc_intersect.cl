/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_intersect.cl                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 11:11:30 by lgatibel          #+#    #+#             */
/*   Updated: 2017/02/13 11:11:39 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float			float3_to_float(float3 v){
	return (v.x + v.y + v.z);
}

void			calc_intersect(float *delta, t_data *data)
{
	///////////////reduire le nombre d'argument a data et delta
	data->intersect = data->ray_pos + (data->ray_dir * (*delta));
	data->grid_intersect = data->ray_pos + (data->grid_ray_dir * (*delta));
}

short			disk_intersection(t_data *data)
{
	float	div;
	float	t;
	float3	pos;

	// rotate_ray(&data->ray_dir, data);////////////not good for plane rotation
	// div = dot(data->obj->rot, data->ray_dir);
	pos = data->pos;
	div = dot(data->rot, data->ray_dir);
	if (div == 0.0f)
		return (0);
	// t = (-dot(data->obj->rot, data->offset)) / div;
	// data->offset = data->ray_pos - pos;

	t = (-dot(data->rot, data->offset)) / div;
	if (t < 0.0f)
		return (0);
	calc_intersect(&t, data);
		if (data->radius != 0.0f && fast_distance(data->grid_intersect,
		 pos) > data->radius)
		//  if (data->obj->radius != 0.0f && fast_distance(data->grid_intersect,
		//  pos) > data->obj->radius)
			// return (0);
		return (0);
	t += (t < 0)? t * -PLANE_PREC: t * -PLANE_PREC;
	return (1);
}

short			plane_intersection(t_data *data)
{
	float	div;
	float	t;

	// data->obj->rot = data->rot;
	
	rotate_ray(&data->ray_dir, data);
	div = dot(data->obj->rot, data->ray_dir);
	if (div == 0.0f)
		return (0);
	t = (-dot(data->obj->rot, data->offset)) / div;
	if (t < 0.0f)
		return (0);
	calc_intersect(&t, data);
	if (data->obj->width != 0.0f && fast_distance(data->grid_intersect.x,
	 data->obj->pos.x) > (data->obj->width / 2.0f))
		return (0);
	if (data->obj->width != 0.0f && fast_distance(data->grid_intersect.z,
	 data->obj->pos.z) > (data->obj->height / 2.0f))
		return (0);
	// t += (t < 0)? t * -PLANE_PREC: t * -PLANE_PREC;///inutile
	// PRINT3(data->obj->rot,"normal");
	return (1);
}

short			cone_intersection(t_data *data)
{
	float	a;
	float	b;
	float	c;
	float	delta;

	float	rad;
	rad = (data->obj->radius / 2.0f) * (float)(M_PI / 180.0f);

	data->ray_dir = rotate_ray(&data->ray_dir, data);
	a = dot(data->ray_dir.xz, data->ray_dir.xz) - dot(data->ray_dir.y,
	 data->ray_dir.y) * tan(rad);

	b = (2.0f * dot(data->ray_dir.x, data->offset.x)) +
	 (2.0f * dot(data->ray_dir.z, data->offset.z)) -
	 (2.0f * dot(data->ray_dir.y, data->offset.y)) * tan(rad);

	c = dot(data->offset.xz, data->offset.xz) -
	 dot(data->offset.y, data->offset.y) * tan(rad);
	if ((delta = calc_delta(a, b, c)) < 0.0f)
		return (0);
	calc_intersect(&delta, data);
	if ((data->obj->height > 0.0f && ((fast_distance(data->obj->pos, data->grid_intersect) >
	 sqrt(data->obj->height * data->obj->height + data->obj->radius  * data->obj->radius)))) ||
		 data->grid_intersect.y >
	data->obj->height || data->grid_intersect.y > data->obj->pos.y)
		return (0);
	// if (data->obj->height > 0.0f && ((sqrt(dot(data->obj->pos - data->grid_intersect,
	// 	data->obj->pos - data->grid_intersect)) > sqrt(data->obj->height *
	// 	data->obj->height + data->obj->radius  * data->obj->radius))))
	// 	return (0);
	return (1);
}


short			cylinder_intersection(t_data *data)
{
	float	a;
	float	b;
	float	c;
	float	delta;

	float3	rdir;
	rdir = data->ray_dir;

	data->ray_dir = rotate_ray(&data->grid_ray_dir, data);
	a = dot(data->ray_dir.x, data->ray_dir.x) + dot(data->ray_dir.z, data->ray_dir.z);
	b = (2.0f * dot(data->ray_dir.x, data->offset.x)) + (2.0f * dot(data->ray_dir.z, data->offset.z));
	c = dot(data->offset.x, data->offset.x) + dot(data->offset.z, data->offset.z) - data->obj->radius *
	data->obj->radius;
	if ((delta = calc_delta(a, b, c)) < 0.0f)
		return (0);
	calc_intersect(&delta, data);
	if (data->obj->height > 0.0f && ((fast_distance(data->obj->pos,data->grid_intersect) > sqrt(data->obj->height *
	data->obj->height + data->obj->radius  * data->obj->radius))))
	{
		// data->test = T_DISK;
		// data->radius = data->obj->radius;
		// if (data->ray_pos.y - data->intersect.y > data->obj->height)
		// {
		// 	data->rot = (float3){0.0f, .0f, 1.0f};
		// 	data->pos = (float3){data->obj->pos.x, data->obj->pos.y - data->obj->height,
		// 	data->obj->pos.z};
		// 	// data->obj->pos.y += data->obj->height;
		// }
		// else
		// {
		// 	data->rot = (float3){0.0f, .0f, 1.0f};
		// 	data->pos = (float3){data->obj->pos.x, data->obj->pos.y + data->obj->height,
		// 	data->obj->pos.z};
		// 	// data->obj->pos = (float3){data->obj->pos.x, data->obj->pos.y + data->obj->height,
		// 	// data->obj->pos.z};
		// }
		// data->ray_dir = rdir;
		// if (disk_intersection(data) == 1)
		// // if (sphere_intersection(data) == 1)/// not working a 100%
		// 	return (1);
		return (0);
	}
	data->test = T_CYLINDER;
	// return (0);
	return (1);
}

short			sphere_intersection(t_data *data)
{
	float	a;
	float	b;
	float	c;
	float	delta;

	data->ray_dir = rotate_ray(&data->ray_dir, data);
	a = dot(data->ray_dir, data->ray_dir);
	b = (2.0f * dot(data->ray_dir.x, data->offset.x)) + (2.0f * dot(data->ray_dir.y, data->offset.y)) +
	 (2.0f * dot(data->ray_dir.z, data->offset.z));
	c = dot(data->offset, data->offset) - data->obj->radius * data->obj->radius;
	if ((delta = calc_delta(a, b, c)) < 0.0f)
		return (0);
	calc_intersect(&delta, data);
	return (1);
}
