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
}

short			disk_intersection(t_data *data, short *index)
{
	float	div;
	float	t;
	float3	rot;

	rot = rotate_ray(&data->rot, data, index);
	div = dot(rot, data->ray_dir);
	if (div == 0.0f)
		return (0);
	t = (-dot(rot, data->offset)) / div;
	if (t < 0.0f)
		return (0);
	calc_intersect(&t, data);
	return (1);
}

short			plane_intersection(t_data *data, short *index)
{
	float	div;
	float	t;
	float3	rot;

	rot = rotate_ray(&data->rot, data, index);
	data->offset = data->ray_pos - data->objs[(int)*index].pos;

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
	float3	rot;

	float	rad;
	rad = (data->objs[(int)*index].radius / 2.0f) * (float)(M_PI / 180.0f);

	float tanj;
	tanj = 1.0f + tan(rad) * tan(rad);
	
	rot = rotate_ray(&data->rot, data, index);
	data->offset = data->ray_pos - data->objs[(int)*index].pos;

	a = dot(data->ray_dir, data->ray_dir) - tanj *
		dot(data->ray_dir, rot) * dot(data->ray_dir, rot);

	b = 2.0f * (dot(data->ray_dir, data->offset) - tanj *
		dot(data->ray_dir, rot) *
		dot(data->offset, rot));

	c = dot(data->offset, data->offset) - tanj *
		dot(data->offset, rot) * dot(data->offset, rot);

	if ((delta = calc_delta(a, b, c)) < 0.0f)
		return (0);
	calc_intersect(&delta, data);
	return (1);
}


short			cylinder_intersection(t_data *data, short *index)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3	rot;

	rot = rotate_ray(&data->rot, data, index);
	data->offset = data->ray_pos - data->objs[(int)*index].pos;

	a = dot(data->ray_dir, data->ray_dir) -
	 dot(data->ray_dir, rot) *
	 dot(data->ray_dir, rot);

	b = 2.0f * (dot(data->ray_dir, data->offset) - 
	dot(data->ray_dir,	rot) *
	dot(data->offset, rot));

	c = dot(data->offset, data->offset) -
	 dot(data->offset,	rot) * dot(data->offset, rot) -
	 data->objs[(int)*index].radius * data->objs[(int)*index].radius;

	if ((delta = calc_delta(a, b, c)) < 0.0f)
		return (0);
	calc_intersect(&delta, data);
	return (1);
}

short			sphere_intersection(t_data *data, short *index)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3	rot;

	rot = rotate_ray(&data->ray_dir, data, index);
	data->offset = data->ray_pos - data->objs[(int)*index].pos;
	
	a = dot(data->ray_dir, data->ray_dir);
	b = 2.0f * dot(data->ray_dir, data->offset);
	c = dot(data->offset, data->offset) - data->objs[(int)*index].radius *
	 data->objs[(int)*index].radius;
	if ((delta = calc_delta(a, b, c)) < 0.0f)
		return (0);
	calc_intersect(&delta, data);
	return (1);
}
