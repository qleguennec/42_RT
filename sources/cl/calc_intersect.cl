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
	data->intersect = data->ray_pos + (data->ray_dir * (*delta));
	data->grid_intersect = data->ray_pos + (data->grid_ray_dir * (*delta));
}

short			disk_intersection(t_data *data, short *index)
{
	float	div;
	float	t;
	// float3	rot;

	// rot = rotate_ray(&data->rot, data, index);

	div = dot(data->rot, data->rdir);
	if (div == 0.0f)
		return (0);
	t = (-dot(data->rot, data->offset)) / div;
	if (t < 0.0f)
		return (0);
	calc_intersect(&t, data);

	if (data->option == 1)
		data->pos = data->objs[(int)*index].pos;
	if (data->objs[(int)*index].radius > 0.0f && fast_distance(data->grid_intersect,
	 data->pos) > data->objs[(int)*index].radius)
		return (0);
	
	return (1);
}

short			plane_intersection(t_data *data, short *index)
{
	float	div;
	float	t;
	float3	rot;

	rot = rotate_ray(&data->rot, data, index);

	div = dot(data->ray_dir, rot);
	if (div == 0.0f)
		return (0);
	t = (-dot(data->offset, rot)) / div;
	if (t < 0.0f)
		return (0);
	calc_intersect(&t, data);
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
	float3	rot;

	rot = rotate_ray(&data->rot, data, index);

	a = dot(data->rdir, data->rdir) -
	 dot(data->rdir, rot) *
	 dot(data->rdir, rot);

	b = 2.0f * (dot(data->rdir, data->offset) - 
	dot(data->rdir,	rot) *
	dot(data->offset, rot));

	c = dot(data->offset, data->offset) -
	 dot(data->offset,	rot) * dot(data->offset, rot) -
	 data->objs[(int)*index].radius * data->objs[(int)*index].radius;

	if ((delta = calc_delta(a, b, c)) < 0.0f)
		return (0);
	calc_intersect(&delta, data);

	return (1);



	
	m = dot(data->rdir, data->rot) * delta + dot(data->offset, data->rot);
	// if (m < -data->objs[(int)*index].height / 2.0f || m > data->objs[(int)*index].height / 2.0f)
	if (data->objs[(int)*index].height > 0.0f && (m < 0.0f || m > data->objs[(int)*index].height))
	{
		data->test = T_DISK;
		if (m < 0.0f)
			 return (disk_intersection(data, index));
		else
		{
			// printf("test\n");
			data->option = 2;
			data->pos = data->objs[(int)*index].pos + (data->rot * data->objs[(int)*index].height);
			 return (disk_intersection(data, index));
		}
			// return (0);
	}
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
	c = dot(data->offset, data->offset) - data->objs[(int)*index].radius *
	 data->objs[(int)*index].radius;
	if ((delta = calc_delta(a, b, c)) < 0.0f)
		return (0);
	calc_intersect(&delta, data);
	return (1);
}
