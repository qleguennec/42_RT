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

#include "obj_def.h"
#include "calc.cl"

kernel void
	kernel_entry
	(global unsigned int *img_buffer
	, global t_obj *objs
	, global t_lgt *lgts
	, global t_cam *cam
	, short nobjs
	, short nlgts)
{
	float3		ray_origin;
	float3		ray_dir;
	float		u;
	float		v;
	size_t		i;
	size_t		j;

	i = get_local_id(0);
	j = get_local_id(1);
	u = cam->pos.x;
	u -= 3 / WIDTH * u;
	u += 0.5 + i;
	u = cam->pos.y;
	v -= 3 / HEIGHT * v;
	v += 0.5 + j;
	ray_origin = cam->pos;
	ray_dir.x = ray_origin.x * u;
	ray_dir.y = ray_origin.y * v;
	ray_dir.z = - cam->focal * ray_origin.z;
	/* call calc
	calc(obj + i * WIDTH * sizeof(*objs) + j * sizeof(*objs)
		, objs
		, lgts
		, nobjs
		, cam
		, nlgts);
	*/
}
