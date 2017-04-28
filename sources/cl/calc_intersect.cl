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
	float3	rot;
	float	div;
	float	t;

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
	float3	disc;
	float3	rot;
	float	delta;
	float	m;
	float	tanj;
	float	rad;

	rad = (data->objs[(int)*index].radius / 2.0f) * (float)(M_PI / 180.0f);
	tanj = 1.0f + tan(rad) * tan(rad);
	rot = rotate_ray(&data->rot, data, index);
	data->offset = data->ray_pos - data->objs[(int)*index].pos;
	disc.x = dot(data->ray_dir, data->ray_dir) - tanj *
		dot(data->ray_dir, rot) * dot(data->ray_dir, rot);
	disc.y = 2.0f * (dot(data->ray_dir, data->offset) - tanj *
		dot(data->ray_dir, rot) *
		dot(data->offset, rot));
	disc.z = dot(data->offset, data->offset) - tanj *
		dot(data->offset, rot) * dot(data->offset, rot);
	if ((delta = calc_delta(&disc, data)) < 0.0f)
		return (0);
	calc_intersect(&delta, data);
    m = dot(data->ray_dir, rot * data->t) + dot(rot, data->offset);
	// if (data->objs[(int)*index].height > 0.0f && 
	// 	(m > data->objs[(int)*index].height || m < 0.0f))
	// 		return (cone_caps(data, &rot, index, m));
	return (1);
}


short			cylinder_intersection(t_data *data, short *index)
{
	float3	disc;
	float3	rot;
	float	delta;
	float	m;

	rot = rotate_ray(&data->rot, data, index);
	data->offset = data->ray_pos - data->objs[(int)*index].pos;
	disc.x = dot(data->ray_dir, data->ray_dir) -
		dot(data->ray_dir, rot) * dot(data->ray_dir, rot);
	disc.y = 2.0f * (dot(data->ray_dir, data->offset) - 
		dot(data->ray_dir, rot) * dot(data->offset, rot));
	disc.z = dot(data->offset, data->offset) -
		dot(data->offset, rot) * dot(data->offset, rot) -
		data->objs[(int)*index].radius * data->objs[(int)*index].radius;
	if ((delta = calc_delta(&disc, data)) == -1)
		return (0);
	else if (!delta)
	{
		calc_intersect(&data->t, data);
		data->type = T_DISK;
		return (1);
		m = dot(data->ray_dir, rot * data->t) + dot(rot, data->offset);
		// if (m < 0.0f || m > 40.0f)
		// 	// return (cylinder_caps(data, &rot, index, m));
		// // else
		// 	return (0);
	}
	else
	{
		calc_intersect(&data->t, data);
		// data->type = T_DISK;
		//  return (1);
		float	m0 = dot(data->ray_dir, rot * data->t0) + dot(rot, data->offset);
		float	m1 = dot(data->ray_dir, rot * data->t1) + dot(rot, data->offset);
		m = (m0 < m1) ? m0 : m1;
		if ((m0 < 0.0f || m1 > 40.0f) && (m1 < 0.0f || m0 > 40.0f))
			return (0);
		// else if ()
			// return (cylinder_caps(data, &rot, index, m));
			// return (0);
		}
	// m = dot(data->ray_dir, rot * data->t) + dot(rot, data->offset);

	// printf("t0[%f], t1[%f], m0[%f], m1[%f]\n", data->t0, data->t1, m0, m1);
	
		// return (0);
	// if (data->objs[(int)*index].height > 0  && (m < 0.0f ||
		// m > data->objs[(int)*index].height))
		// return (0);
	return (1);
}

short			sphere_intersection(t_data *data, short *index)
{
	float3	disc;
	float3	rot;
	float	delta;

	rot = rotate_ray(&data->ray_dir, data, index);
	data->offset = data->ray_pos - data->objs[(int)*index].pos;
	disc.x = dot(data->ray_dir, data->ray_dir);
	disc.y = 2.0f * dot(data->ray_dir, data->offset);
	disc.z = dot(data->offset, data->offset) -
	data->objs[(int)*index].radius * data->objs[(int)*index].radius;
	if ((delta = calc_delta(&disc, data)) < 0.0f)
		return (0);
	calc_intersect(&delta, data);
	return (1);
}
