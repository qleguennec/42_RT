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

#define DEBUG 0

#define PRINT3(v, a) printf(a ": %f %f %f\n", (v).x, (v).y, (v).z);
#define PRINT1(v, a) printf(a ": %f\n", (v));

constant float2	size2	= (float2){WIDTH, HEIGHT};
constant float2	size2_2	= (float2){XCENTER, YCENTER};
constant float3	size3	= (float3){WIDTH, HEIGHT, 1};
constant float3	size3_2	= (float3){XCENTER, YCENTER, 1};

# include "calc.cl"

#if DEBUG
# include "debug.cl"
#endif
/*
void
	test_sphere_intersection
	(global unsigned int *img_buffer
	, global t_cam *cam
	, global t_obj *objs
	, global t_lgt *lgts
	, short nobjs
	, short nlgts
	, float3 o
	, float3 d)
{
	float	delta;
	float3	center;
	float	radius;
	float3 offset;

	center = (float3){-50, 50, -10};
	offset = cam->pos - center;
	radius = 10.0;
	delta = dot(d, offset);
	delta *= delta;
	delta -= dot(d, d) * (dot(offset, offset) - radius * radius);
	if (delta >= 0)
	{
		*img_buffer = 0xffffffff;
	}
}
*/
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
	float2	indent;
	float3	direction;
	size_t	x;
	size_t	y;

	x = get_global_id(0);
	y = get_global_id(1);
#if DEBUG
	if (x == 0 && y == 0)
		debug(objs, lgts, cam, nobjs, nlgts);
#endif
	direction.xy = size2_2 - (float2){x - .5, y - .5};
	direction.z = 55;
	direction = normalize(direction);
	if (x == 0 && y == 0)
		PRINT3(direction, "direction");
	if (x == XCENTER && y == YCENTER)
		PRINT3(direction, "direction");
	if (x == WIDTH - 1 && y == HEIGHT - 1)
		PRINT3(direction, "direction");
/*
	test_sphere_intersection(img_buffer + WIDTH * y + x
		, cam
		, objs
		, lgts
		, nobjs
		, nlgts
		, cam->pos
		, direction);
*/
	calc(0,img_buffer + WIDTH * y + x
		, objs
		, lgts
		, nobjs
		, nlgts
		, cam->pos
		, direction
		, cam);
}
