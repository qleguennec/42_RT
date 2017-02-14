/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_main_krl_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 12:07:51 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/14 15:19:40 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libfmt.h"

bool
	cl_main_krl_exec
	(t_cl *cl
	, t_scene *scn)
{
	int			ret;
	size_t		work_size[2];

	if (!cl_main_krl_update_camera(cl, scn->c_cam))
		return (ERR("cannot update camera", false, 0));
	if (!cl_main_krl_update_buffers(cl, scn))
		return (ERR("cannot update buffers", false, 0));
	work_size[0] = WIN_W;
	work_size[1] = WIN_H;
	if ((ret = cl_krl_exec(&cl->info, cl->main_krl.krl, 2, work_size))
		!= CL_SUCCESS)
		return (ERR("cannot exec kernel, err %a", false, ret));
	return (true);
}
