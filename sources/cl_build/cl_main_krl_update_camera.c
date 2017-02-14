/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_main_krl_update_camera.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 10:39:33 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/13 16:03:02 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_interface.h"
#include "libfmt.h"
#include "rt.h"

// TODO remove debug includes
#include <assert.h>

bool
	cl_main_krl_update_camera
	(t_cl *cl
	, t_obj *obj)
{
	int			ret;
	t_cl_cam	cam;

	//assert(obj->type = 'C');
	cpy_cam(&cam, obj);
	if ((ret = cl_write(&cl->info, cl->main_krl.args[1], sizeof(cam), &cam))
		!= CL_SUCCESS)
		return (ERR("cannot set camera, err %a", false, ret));
	return (true);
}
