/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ray_send.cl                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 07:50:15 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/08 07:50:16 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_cl_interface.h"

kernel void
	rt_ray_send
	(global unsigned int *rays
	, global t_obj *objs
	, size_t nobjs)
{
	double3		ray_origin;
	double		ray_dir;
	double		u;
	double		v;
	double		delta;
	double3		obj_dist;
	t_obj		cam;
	t_obj		sphere;

	cam = objs[0];
	sphere = objs[1];
	u = cam.pos.x;
	u -= 3 / WIDTH * u;
	u += 0.5 + get_local_id(0);
	u = cam.pos.y;
	v -= 3 / HEIGHT * v;
	v += 0.5 + get_local_id(1);
	ray_origin = cam.pos;
	ray_dir = - 10 * ray_origin.z + u * ray_origin.x + v * ray_origin.y;
	obj_dist = ray_origin - sphere.pos;
	delta = 
}
