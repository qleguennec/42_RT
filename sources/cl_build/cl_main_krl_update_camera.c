/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_main_krl_update_camera.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 10:39:33 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/12 16:10:09 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_interface.h"
#include "rt.h"

// TODO remove debug includes
#include <assert.h>

bool
	cl_main_krl_update_camera
	(t_cl *cl
	, t_obj *obj)
{
	t_cl_cam	cam;

	assert(obj->type == 'C');
	cam.pos.x = obj->pos.x;
	cam.pos.y = obj->pos.y;
	cam.pos.z = obj->pos.z;
	cam.rot.x = obj->rot.x;
	cam.rot.y = obj->rot.y;
	cam.rot.z = obj->rot.z;
	cam.focal = obj->focal;
	CL_KRL_ARG(cl->main_krl.krl, 3, cam);
	return (true);
}
