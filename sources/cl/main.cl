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

#include "debug.h"

#include "calc.cl"

constant float2	size2	= (float2){WIDTH, HEIGHT};
constant float2	size2_2	= (float2){XCENTER, YCENTER};
constant float3	size3	= (float3){WIDTH, HEIGHT, 0};
constant float3	size3_2	= (float3){XCENTER, YCENTER, 0};

#if DEBUG
# include "debug.cl"
#endif

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
	float3	origin;
	float3	rot;
	size_t	x;
	size_t	y;

	x = get_global_id(0);
	y = get_global_id(1);
	if (DEBUG && x == 0 && y == 0)
		debug(objs, lgts, cam, nobjs, nlgts);
	basis.y = 1.0f;
	basis.x = WIDTH / HEIGHT;
	indent.y = basis.y / HEIGHT;
	indent.x = basis.x / WIDTH;

	rot = (float3){0.0f, 0.0f, 1.0f};
	rot = rotate_cam(&rot, cam->rot);
	origin.x = cam->pos.x + (cam->focal / 27.5f * rot.y) - basis.x / 2.0f;
	origin.y = cam->pos.y + (cam->focal / 27.5f * rot.x) - basis.y / 2.0f;
	origin.z = cam->pos.z + (cam->focal / 27.5f * rot.z);
	direction.x = origin.x + ((float)x * indent.x) - cam->pos.x;
	direction.y = origin.y + ((float)y * indent.y) - cam->pos.y;
	direction.z = origin.z - cam->pos.z;
	*(img_buffer + WIDTH * y + x) = -1;
	if ((x == XCENTER && y == YCENTER))
	PRINT3(fast_normalize(direction),"direction");
	// if ((x > XCENTER - 10 && y > YCENTER - 10 && x < XCENTER + 10 && y < YCENTER + 10))
	calc_picture((DEBUG && ((x == XCENTER && y == YCENTER) || (x == XCENTER && y == YCENTER)))
		, img_buffer + WIDTH * y + x
		, objs
		, lgts
		, nobjs
		, nlgts
		, cam->pos
		, fast_normalize(direction)
		, cam, x, y);
}
