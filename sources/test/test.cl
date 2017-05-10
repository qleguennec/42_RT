# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.cl                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/10 11:47:35 by qle-guen          #+#    #+#              #
#    Updated: 2017/05/10 10:42:10 by bsouchet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#include "obj_def.h"

void
	print_cam
	(global t_cam *cam)
{
	printf("\tpos: %f %f %f\n", cam->pos.x, cam->pos.y, cam->pos.z);
	printf("\trot: %f %f %f\n", cam->rot.x, cam->pos.y, cam->pos.z);
	printf("\tfocal: %d\n", cam->focal);
}

void
	print_obj
	(t_obj obj)
{
	printf("\tpos: %f %f %f\n", obj.pos.x, obj.pos.y, obj.pos.z);
	printf("\trot: %f %f %f\n", obj.rot.x, obj.rot.y, obj.rot.z);
	printf("\tclr: %f %f %f\n", obj.clr.x, obj.clr.y, obj.clr.z);
	printf("\topacity: %f\n", obj.opacity);
	printf("\tspecolor: %f\n", obj.specolor);
	printf("\treflex: %f\n", obj.reflex);
	printf("\trefrac: %f\n", obj.refrac);
	if (obj.type == TYPE_SPHERE)
	{
		printf("\ttype: sphere\n");
		printf("\t\tradius: %d", obj.radius);
	}
	else if (obj.type == TYPE_CUBE)
	{
		printf("\ttype: cube\n");
		printf("\t\twidth: %d", obj.width);
		printf("\theight: %d", obj.height);
	}
	else
		printf("\ttype: unknown\n");
}

void
	print_light
	(t_lgt lgt)
{
	printf("\tpos: %f %f %f\n", lgt.pos.x, lgt.pos.y, lgt.pos.z);
	printf("\trot: %f %f %f\n", lgt.rot.x, lgt.pos.y, lgt.pos.z);
	printf("\tintensity: %f\n", lgt.intensity);
	printf("\tshiness: %f\n", lgt.shiness);
	printf("\tmshiness: %f\n", lgt.mshiness);
}

kernel void
	test
	(global uint *img_buffer
	, global t_cam *cam
	, global t_obj *objs
	, global t_lgt *lgts
	, short nobjs
	, short nlgts)
{
	short	i;

	printf("nobjs: %d\n", nobjs);
	printf("nlgts: %d\n", nlgts);
	printf("active camera:\n");
	print_cam(cam);
	i = 0;
	while (i < nobjs)
	{
		printf("object %d:\n", i);
		print_obj(objs[i]);
		printf("\n");
		i++;
	}
	i = 0;
	while (i < nlgts)
	{
		printf("light %d:\n", i);
		print_light(lgts[i]);
		i++;
	}
}
