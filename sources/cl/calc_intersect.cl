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

void			calc_intersect(float *delta, float3 *ray_pos, float3 *ray_dir,
 float3 *intersect)
{
	*intersect = *ray_pos + (*ray_dir * (*delta));
}

short			plane_intersection(t_data *data)
{
	float	div;
	float	t;
	// float3	ray_dir;

	// ray_dir = data->ray_dir;
	data->offset = data->ray_pos - data->obj->pos;
	div = dot(data->obj->rot, data->ray_dir);
	if (div == 0.0f)
		return (0);
	t = (-dot(data->obj->rot, data->offset)) / div;
	if (t < 0.0f)
		return (0);
	calc_intersect(&t, &data->ray_pos, &data->ray_dir, &data->intersect);
	return (1);
}

short			cone_intersection(t_data *data)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3 	ray_dir;
	float3	rdir;

	ray_dir = data->ray_dir;
	rdir = ray_dir;
	data->offset = data->ray_pos - data->obj->pos;

	// ray_dir = rotate_ray(&ray_dir, data);

	a = dot(ray_dir.xz, ray_dir.xz) - dot(ray_dir.y, ray_dir.y);// * tan(rad);

	b = (2.0f * dot(ray_dir.x, data->offset.x)) + (2.0f * dot(ray_dir.z, data->offset.z)) -
	 (2.0f * dot(ray_dir.y, data->offset.y));// * tan(rad));

	c = dot(data->offset.xz, data->offset.xz) - dot(data->offset.y, data->offset.y);// * (tan(rad));
	if ((delta = calc_delta(a, b, c)) < 0.0f)
		return (0);
	// calc_intersection(&delta, &data->ray_pos, &ray_dir, &data->intersect);
	calc_intersect(&delta, &data->ray_pos, &ray_dir, &data->intersect);

/*	float test = 1.0f;
	if (obj->height > 0.0f && (sqrt(dot(data->intersect - obj->pos,
					data->intersect - obj->pos)) > sqrt((test * obj->height) *
					 (test * obj->height) + obj->radius  * obj->radius) ||
			dot(data->intersect, obj->pos) < 0.0f))
		return (0);
*/
	return (1);
}


short			cylinder_intersection(t_data *data)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3 	ray_dir;
	float3 rdir;

	ray_dir = data->ray_dir;
	data->offset = data->ray_pos - data->obj->pos;
	rdir = ray_dir;
	ray_dir = rotate_ray(&ray_dir, data);
	// PRINT3(ray_dir, "ray_dir");
	a = dot(ray_dir.x, ray_dir.x) + dot(ray_dir.z, ray_dir.z);
	b = (2.0f * dot(ray_dir.x, data->offset.x)) + (2.0f * dot(ray_dir.z, data->offset.z));
	c = dot(data->offset.x, data->offset.x) + dot(data->offset.z, data->offset.z) - data->obj->radius *
	data->obj->radius;
	if ((delta = calc_delta(a, b, c)) < 0.0f)
		return (0);
	// ray_dir = rdir;
	calc_intersect(&delta, &data->ray_pos, &ray_dir, &data->intersect);
		//test de la troncature du cylindre
		// if (data->obj->height > 0.0f && sqrt(dot(data->intersect - data->obj->pos,
		// data->intersect - data->obj->pos)) <= sqrt(data->obj->height * data->obj->height +
		// data->obj->radius * data->obj->radius))
		// return (0);
		///////////////
	return (1);
}

short			sphere_intersection(t_data *data)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3 	ray_dir;

	ray_dir = data->ray_dir;
	data->offset = data->ray_pos - data->obj->pos;
	ray_dir = rotate_ray(&ray_dir, data);
	
	a = dot(ray_dir, ray_dir);
	b = (2.0f * dot(ray_dir.x, data->offset.x)) + (2.0f * dot(ray_dir.y, data->offset.y)) +
	 (2.0f * dot(ray_dir.z, data->offset.z));
	c = dot(data->offset, data->offset) - data->obj->radius * data->obj->radius;
	if ((delta = calc_delta(a, b, c)) < 0.0f)
		return (0);
	calc_intersect(&delta, &data->ray_pos, &ray_dir, &data->intersect);

	return (1);
}
