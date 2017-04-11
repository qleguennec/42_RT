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
	data->t = *delta;
	data->intersect = data->ray_pos + (data->rdir * (*delta));
	data->grid_intersect = data->ray_pos + (data->grid_ray_dir * (*delta));
}

short			disk_intersection(t_data *data, short *index)
{
	float	div;
	float	t;

	// data->option = 0;
	// data->rot = rotate_ray(&data->rot, data);
	// rotate_ray(&data->ray_dir, data, index);
	// data->offset = data->ray_pos - data->pos;
	data->rdir = rotate_ray(&data->ray_dir, data, index);
	// rotate_ray(&data->ray_dir, data, index);
	//  data->offset = data->ray_pos - data->objs[(int)*index].pos;

	div = dot(data->rot, data->rdir);
	if (div == 0.0f)
		return (0);
	t = (-dot(data->rot, data->offset)) / div;
	if (t < 0.0f)
		return (0);
	t += (t < 0)? t * -PLANE_PREC: t * PLANE_PREC;
	calc_intersect(&t, data);
	if (data->objs[(int)*index].radius > 0.0f && fast_distance(data->grid_intersect,
	 data->pos) > data->objs[(int)*index].radius)
		return (0);
	return (1);
}

short			plane_intersection(t_data *data, short *index)
{
	float	div;
	// float	delta;
	float	t;

	// data->option = 2;
	// data->rot = rotate_ray(&data->rot, data);
	// data->rdir = rotate_ray(&data->ray_dir, data, index);
	// data->offset = data->ray_pos - data->objs[(int)*index].pos;
/*
	div = dot((float3){0.0f, 1.0f, 0.0f}, data->rdir);
	if (div == 0.0f)
		return (0);
	t = (-dot((float3){0.0f, 1.0f, 0.0f}, data->offset)) / div;
	if (t < 0.0f)
		return (0);
	t += (t < 0)? t * -PLANE_PREC: t * PLANE_PREC;
	data->delta = t;
*/
return (1);
	div = dot(data->rdir, data->rot);
	if (div == 0.0f)
		return (0);
	t = (-dot(data->offset, data->rot)) / div;
	if (t < 0.0f)
		return (0);
	t += (t < 0)? t * -PLANE_PREC: t * PLANE_PREC;
	calc_intersect(&t, data);
	// if (data->objs[(int)*index].width > 0.0f && fast_distance(data->grid_intersect.x,
	//  data->objs[(int)*index].pos.x) > (data->objs[(int)*index].width / 2.0f))
	// 	return (0);
	// if (data->objs[(int)*index].height > 0.0f && fast_distance(data->grid_intersect.z,
	//  data->objs[(int)*index].pos.z) > (data->objs[(int)*index].height / 2.0f))
	// 	return (0);
	// data->radius = 4;
	// if (data->radius > 0.0f && fast_distance(data->grid_intersect,
	//  data->objs[(int)*index].pos) > data->radius)
	// 	return (0);
//	 if (data->objs[(int)*index].width > 0.0f && fast_distance(data->grid_intersect.x,
//	  data->objs[(int)*index].pos.x) > (data->objs[(int)*index].width / 2.0f))
//	 	return (0);
//	 if (data->objs[(int)*index].height > 0.0f && fast_distance(data->grid_intersect.z,
//	  data->objs[(int)*index].pos.z) > (data->objs[(int)*index].height / 2.0f))
//	 	return (0);
	// PRINT3(data->objs[(int)*index].rot,"normal");
	return (1);
}

short			cone_intersection(t_data *data, short *index)
{
	float	a;
	float	b;
	float	c;
	float	delta;

	float	rad;
	rad = (data->objs[(int)*index].radius / 2.0f) * (float)(M_PI / 180.0f);

	float tanj;
	tanj = 1.0f + tan(rad) * tan(rad); 
	
	data->rdir = rotate_ray(&data->ray_dir, data, index);

	a = dot(data->rdir, data->rdir) - tanj *
		dot(data->rdir, data->rot) * dot(data->rdir, data->rot);

	b = 2.0f * (dot(data->rdir, data->offset) - tanj *
		dot(data->rdir, data->rot) *
		dot(data->offset, data->rot));

	c = dot(data->offset, data->offset) - tanj * 
		dot(data->offset, data->rot) * dot(data->offset, data->rot);

	if ((delta = calc_delta(a, b, c)) < 0.0f)
		return (0);
	calc_intersect(&delta, data);

	if ((data->objs[(int)*index].height > 0.0f && ((fast_distance(data->objs[(int)*index].pos, data->grid_intersect) >
	sqrt(data->objs[(int)*index].height * data->objs[(int)*index].height + data->objs[(int)*index].radius  * data->objs[(int)*index].radius)))))
		return (0);
	return (1);
}


short			cylinder_intersection(t_data *data, short *index)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float	m;

	data->rdir = rotate_ray(&data->ray_dir, data, index);

	a = dot(data->rdir, data->rdir) -
	 dot(data->rdir, data->rot) *
	 dot(data->rdir, data->rot);

	b = 2.0f * (dot(data->rdir, data->offset) - 
	dot(data->rdir,	data->rot) *
	dot(data->offset, data->rot));

	c = dot(data->offset, data->offset) -
	 dot(data->offset,	data->rot) * dot(data->offset, data->rot) -
	 data->objs[(int)*index].radius * data->objs[(int)*index].radius;

	if ((delta = calc_delta(a, b, c)) < 0.0f)
		return (0);

	calc_intersect(&delta, data);
	m = dot(data->rdir, data->rot) * delta + dot(data->offset, data->rot);
	// if (m < -data->objs[(int)*index].height / 2.0f || m > data->objs[(int)*index].height / 2.0f)
	if (m > 0.0f || m < -data->objs[(int)*index].height)
	{
		// if (m > 0.0f)
		// {	
		// 	// data->rot = (float3){-1.0f, 0.0f, 0.0f};
		// 	// data->rdir = data->ray_dir;
	 	// 	if (!plane_intersection(data, index))
		// 	return (0);
		// }
		// else
		// {
		// 	return (0);
		// }
			return (0);
		
	}
	// if (data->objs[(int)*index].height > 0.0f && ((distance(data->objs[(int)*index].pos, data->grid_intersect) > sqrt(data->objs[(int)*index].height *
	// data->objs[(int)*index].height + data->objs[(int)*index].radius  * data->objs[(int)*index].radius))))
	// {
	// 	// // data->rot = (float3){0.0f, 1.0f, 0.0f};
	// 	// // data->option = 0;
	// 	// // data->radius = data->objs[(int)*index].radius;
	// 	// data->test = T_DISK;
	// 	// // if (data->grid_intersect.y == data->objs[(int)*index].pos.y - data->objs[(int)*index].height || data->grid_intersect.y == data->objs[(int)*index].pos.y + data->objs[(int)*index].height)
	// 	// // {
	// 	// 	if (data->ray_pos.y - data->grid_intersect.y > data->objs[(int)*index].height)
	// 	// 	{
	// 	// 	return (0);
	// 	// 		data->pos = data->objs[(int)*index].pos;
	// 	// 		data->pos.y -= data->objs[(int)*index].height;
	// 	// 	}
	// 	// 	else
	// 	// 	{
	// 	// 		data->pos = data->objs[(int)*index].pos;
	// 	// 		data->pos.y += data->objs[(int)*index].height;
	// 	// 	}
	// 	// 	if (disk_intersection(data))
	// 	// 	// if (sphere_intersection(data))/// not working a 100%
	// 	// 		return (1);
	// 	// 	// }
	// 	return (0);
	// }
		// return (0);
	return (1);
}

short			sphere_intersection(t_data *data, short *index)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	data->rdir = rotate_ray(&data->ray_dir, data, index);
	// data->offset = data->ray_pos - data->pos;
	
	a = dot(data->rdir, data->rdir);
	b = 2.0f * dot(data->rdir, data->offset);
	c = dot(data->offset, data->offset) -  data->objs[(int)*index].radius * data->objs[(int)*index].radius;
	if ((delta = calc_delta(a, b, c)) < 0.0f)
		return (0);
	calc_intersect(&delta, data);
	return (1);
}
