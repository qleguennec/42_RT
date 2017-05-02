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
	if ((delta = calc_delta(&disc, data)) == -1)
		return (0);
	m = dot(data->ray_dir, rot * data->t) + dot(rot, data->offset);
	if (data->objs[(int)*index].height > 0.0f &&
		(m > data->objs[(int)*index].height || m < 0.0f))
	{
		delta = (data->t0 > data->t1) ? data->t0 : data->t1;
		if ((rad = cone_caps(data, &rot, index, m)) == 0)
			return (0);
		else if (rad == 1)
			return (1);
	}
	calc_intersect(&delta, data);
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
	if (data->objs[(int)*index].height > 0.0f)
	{
		m = dot(data->ray_dir, rot * data->t) + dot(rot, data->offset);
		if (m < 0.0f || m > data->objs[(int)*index].height)
			return (cylinder_caps(data, &rot, index, m));
	}
	calc_intersect(&data->t, data);
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
	if ((delta = calc_delta(&disc, data)) == -1)
		return (0);
	calc_intersect(&delta, data);
	return (1);
}

short            egg_intersection(t_data *data, short *index)
{
	float3	disc;
    float    k1;
    float    k2;
    float    sr;
	float	delta;

    sr = pow(data->objs[(int)*index].radius, 2.0f);

    k1 = 2.0f * data->objs[(int)*index].height * (dot(data->ray_dir, data->rot));
    k2 = sr + 2.0f * data->objs[(int)*index].height *
            dot(data->offset, data->rot) - data->objs[(int)*index].height;

    disc.x = dot((4.0f * sr * data->ray_dir), data->ray_dir) - k1 * k1;
    disc.y = 2.0f * (dot((4.0f * sr * data->ray_dir), data->offset) - k1 * k2);
    disc.z = dot((4.0f * sr * data->offset), data->offset) - k2 * k2;

    if ((delta = calc_delta(&disc, data)) < 0.0f)
        return (0);
    calc_intersect(&delta, data);
    return (1);
}

short            paraboloid_intersection(t_data *data, short *index)
{
	float3	disc;
	float	delta;

    disc.x = dot(data->ray_dir, data->ray_dir) - pow(dot(data->ray_dir, data->rot), 2.0f);
    disc.y = 2.0f * (dot(data->ray_dir, data->offset) - dot(data->ray_dir, data->rot) *
        (dot(data->offset, data->rot) + 2.0f * data->objs[(int)*index].height));
    disc.z = dot(data->offset, data->offset) - dot(data->offset, data->ray_dir) *
        (dot(data->offset, data->ray_dir) + 4.0f * data->objs[(int)*index].height);
    if ((delta = calc_delta(&disc, data)) < 0.0f)
        return (0);
    calc_intersect(&delta, data);
    return (1);
}
