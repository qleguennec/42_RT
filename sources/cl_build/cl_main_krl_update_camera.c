/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_main_krl_update_camera.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 10:39:33 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/10 10:48:35 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_interface.h"

bool
	cl_main_krl_update_camera
	(t_cl *cl
	, cl_float3 pos
	, cl_float3 rot
	, short focal)
{
	t_cam	cam;

	cam.pos = pos;
	cam.rot = rot;
	cam.focal = focal;
	return (CL_KRL_ARG(cl->main_krl.krl, 3, cam) == CL_SUCCESS);
}
