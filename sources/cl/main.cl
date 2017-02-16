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

#define DEBUG 1

#define PRINT3(v, a) printf(a ": %f %f %f\n", (v).x, (v).y, (v).z);
#define PRINT1(v, a) printf(a ": %f\n", (v));

constant float2	size2	= (float2){WIDTH, HEIGHT};
constant float2	size2_2	= (float2){XCENTER, YCENTER};
constant float3	size3	= (float3){WIDTH, HEIGHT, 0};
constant float3	size3_2	= (float3){XCENTER, YCENTER, 0};

#include "debug.cl"
#include "calc.cl"

kernel void
	kernel_entry
	(global unsigned int *img_buffer
	, global t_cam *cam
	, global t_obj *objs
	, global t_lgt *lgts
	, short nobjs
	, short nlgts)
{
	float2	basis;
	float3	direction;
	float3	origin;
	size_t	x;
	size_t	y;

	x = get_global_id(0);
	y = get_global_id(1);
	if (DEBUG && x == 0 && y == 0)
		debug(objs, lgts, cam, nobjs, nlgts);
	basis.x = cam->pos.x;
	basis.y = cam->pos.y;
	basis += 0.5 * (1 + basis / size2);
	origin = cam->pos;
	direction.x = x * basis.x;
	direction.y = y * basis.y;
	direction.z = - cam->focal;
	*(img_buffer + WIDTH * y + x) = -1;
	//printf("testing\n");
	calc(img_buffer + WIDTH * y + x
		, objs
		, lgts
		, nobjs
		, nlgts
		, origin
		, normalize(direction)
		, cam);
}
