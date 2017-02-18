/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 14:26:58 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/16 14:27:10 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void
	print_obj_type
	(short type)
{
	if (type == T_SPHERE)
		printf("sphere\n");
	if (type == T_CUBE)
		printf("cube\n");
	if (type == T_CYLINDER)
		printf("cylinder\n");
	if (type == T_PLANE)
		printf("plane\n");
	if (type == T_CONE)
		printf("cone\n");
	if (type == T_TORUS)
		printf("torus\n");
	if (type == T_PYRAMID)
		printf("pyramid\n");
	if (type == T_TETRAHEDRON)
		printf("tetrahedron\n");
	if (type == T_MOEBIUS)
		printf("moebius\n");
}

void
	debug
	(global t_obj *objs
	, global t_lgt *lgts
	, global t_cam *cam
	, short nobjs
	, short nlgts)
{
	short	i;

	i = 0;
	while (i < nobjs)
	{
		printf("obj %d\n", i);
		printf("type: ");
		print_obj_type(objs[i].type);
		PRINT3(objs[i].pos, "pos");
		PRINT3(objs[i].rot, "rot");
		PRINT3(objs[i].clr, "clr");
		PRINT1(objs[i].opacity, "opacity")
		PRINT1(objs[i].width, "width")
		PRINT1(objs[i].height, "height")
		PRINT1(objs[i].radius, "radius")
		PRINT1(objs[i].reflex, "reflex")
		PRINT1(objs[i].refract, "refract")
		PRINT1(objs[i].shiness, "shiness")
		PRINT1(objs[i].mshiness, "mshiness")
		printf("---\n");
		i++;
	}
	i = 0;
	while (i < nlgts)
	{
		printf("lgt %d\n", i);
		PRINT3(lgts[i].pos, "pos");
		PRINT3(lgts[i].rot, "rot");
		PRINT3(lgts[i].clr, "clr");
		PRINT1(lgts[i].intensity, "intensity");
		printf("---\n");
		i++;
	}
	printf("active camera:\n");
	PRINT3((*cam).pos, "pos");
	PRINT3((*cam).rot, "rot");
	printf("focal: %d\n", cam->focal);
	printf("-----------\n");
}
