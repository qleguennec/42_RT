/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 07:50:15 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/08 07:50:16 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_cl_interface.h"

kernel void
	main
	(global unsigned int *img_buffer
	, global t_obj *objs
	, global t_lgts *lgts
	, t_cam cam
	, size_t nobjs
	, size_t nlgts)
{
	double3		ray_origin;
	double		ray_dir;
	double		u;
	double		v;

	u = cam.pos.x;
	u -= 3 / WIDTH * u;
	u += 0.5 + get_local_id(0);
	u = cam.pos.y;
	v -= 3 / HEIGHT * v;
	v += 0.5 + get_local_id(1);
	ray_origin = cam.pos;
	ray_dir = - cam.flocal * ray_origin.z + u * ray_origin.x + v * ray_origin.y;
}
