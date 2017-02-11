/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 11:47:35 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/10 11:51:03 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "obj_def.h"

void
	print_cam
	(t_cam cam)
{
	printf("\tpos: %f %f %f\n", cam.pos);
	printf("\trot: %f %f %f\n", cam.rot);
	printf("\tfocal: %d\n", cam.focal);
}

void
	print_obj
	(t_obj obj)
{
	printf("\tpos: %f %f %f\n", obj.pos);
	printf("\trot: %f %f %f\n", obj.rot);
	printf("\tclr: %f %f %f\n", obj.clr);
	printf("\topacity: %f\n", obj.opacity);
	printf("\tspecolor: %f\n", obj.specolor);
	printf("\treflex: %f\n", obj.reflex);
	printf("\trefract: %f\n", obj.refract);
	if (obj.type == TYPE_SPHERE)
	{
		printf("\ttype: sphere\n");
		printf("\t\tradius: %d", obj.radius);
	}
	else if (obj.type == TYPE_CUBE)
	{
		printf("\ttype: cube\n");
		printf("\t\twidth: %d", obj.width);
		printf("\t\height: %d", obj.height);
	}
	else
		printf("\ttype: unknown\n");
}

void
	print_light
	(t_lgt lgt)
{
	printf("\tpos: %f %f %f\n", lgt.pos);
	printf("\trot: %f %f %f\n", lgt.rot);
	printf("\tintensity: %f\n", lgt.intensity);
	printf("\tshiness: %f\n", lgt.shiness);
	printf("\tmshiness: %f\n", lgt.mshiness);
}

kernel void
	test
	(global unsigned int *img_buffer
	, global t_obj *objs
	, global t_lgt *lgts
	, t_cam cam
	, short nobjs
	, short nlgts)
{
	short	i;

	printf("active camera:\n");
	print_cam(cam);
	i = 0;
	while (i < nobjs)
	{
		printf("object %d:\n", i);
		print_obj(objs[i]);
	}
	i = 0;
	while (i < nlgts)
	{
		printf("light %d:\n", i);
		print_light(lgts[i]);
	}
}
