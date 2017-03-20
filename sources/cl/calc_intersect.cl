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

short			plane_intersection(t_data *data, global t_obj *obj)
{
	float	div;
	float	t;
	float3	ray_dir;
	float3	offset;

	ray_dir = data->ray_dir;
	offset = data->ray_pos - obj->pos;
		return (0);
	div = dot(obj->rot, ray_dir);
	if (div == 0.0f)
		return (0);
	t = (-dot(obj->rot, offset)) / div;
	if (t < 0.0f)
		return (0);
	calc_intersect(&t, &data->ray_pos, &data->ray_dir, &data->intersect);
	return (1);
}

short			cone_intersection(t_data *data, global t_obj *obj)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3	offset;
	float3 	ray_dir;
	float3	rdir;
	
	ray_dir = data->ray_dir;
	rdir = ray_dir;
	offset = data->ray_pos - obj->pos;

	// ray_dir = rotate_x(&ray_dir, obj, &offset);

	a = dot(ray_dir.xz, ray_dir.xz) - dot(ray_dir.y, ray_dir.y);// * tan(rad);

	b = (2.0f * dot(ray_dir.x, offset.x)) + (2.0f * dot(ray_dir.z, offset.z)) -
	 (2.0f * dot(ray_dir.y, offset.y));// * tan(rad));

	c = dot(offset.xz, offset.xz) - dot(offset.y, offset.y);// * (tan(rad));
	if ((delta = calc_delta(a, b, c)) < 0.0f)
		return (0);
	// calc_intersect(&delta, &data->ray_pos, &ray_dir, &data->intersect);
	calc_intersect(&delta, &data->ray_pos, &rdir, &data->intersect);

/*	float test = 1.0f;
	if (obj->height > 0.0f && (sqrt(dot(data->intersect - obj->pos,
					data->intersect - obj->pos)) > sqrt((test * obj->height) *
					 (test * obj->height) + obj->radius  * obj->radius) ||
			dot(data->intersect, obj->pos) < 0.0f))
		return (0);
*/
	return (1);
}


short			cylinder_intersection(t_data *data, global t_obj *obj)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3	offset;
	float3 	ray_dir;
	float3 rdir;

	ray_dir = data->ray_dir;
	offset = data->ray_pos - obj->pos;
	rdir = ray_dir;
//rotation sur x
	//  ray_dir = rotate_x(&ray_dir, obj, &offset);
//rotation sur y
	// ray_dir = rotate_y(&ray_dir, obj, &offset);
//rotation sur z
	// ray_dir = rotate_z(&ray_dir, obj, &offset);
	
	a = dot(ray_dir.x, ray_dir.x) + dot(ray_dir.z, ray_dir.z);
	b = (2.0f * dot(ray_dir.x, offset.x)) + (2.0f * dot(ray_dir.z, offset.z));
	c = dot(offset.x, offset.x) + dot(offset.z, offset.z) - obj->radius * 
	obj->radius;
	if ((delta = calc_delta(a, b, c)) < 0.0f)
		return (0);

	ray_dir = rdir;
	calc_intersect(&delta, &data->ray_pos, &ray_dir, &data->intersect);
		//test de la troncature du cylindre
		// if (obj->height > 0.0f && sqrt(dot(data->intersect - obj->pos,
		// data->intersect - obj->pos)) <= sqrt(obj->height * obj->height +
		// obj->radius * obj->radius))
		// return (0);
		///////////////
	return (1);
}

short			sphere_intersection(t_data *data, global t_obj *obj)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3	offset;
	float3 	ray_dir;

	ray_dir = data->ray_dir;
	offset = data->ray_pos - obj->pos;
	a = 1.0f;
	b = dot(ray_dir, offset);
	c = dot(offset, offset) - obj->radius * obj->radius;
	if ((delta = (b * b) - a *c) < 0.0f)
		return (0);
	delta = sqrt(delta);
	delta = (-(b + delta) < 0.0f) ? -(b - delta): -(b + delta);
	calc_intersect(&delta, &data->ray_pos, &ray_dir, &data->intersect);
	return (1);
}