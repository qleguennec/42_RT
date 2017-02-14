/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_main_krl_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 12:07:51 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/13 15:06:25 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "cl_interface.h"

bool
	cl_main_krl_exec
	(t_cl *cl
	, t_scene *scene)
{
	size_t		work_size[2];

	if (!cl_main_krl_update_buffers(cl, scene))
		return (false);
	work_size[0] = WIN_W;
	work_size[1] = WIN_H;
	return (cl_krl_exec(&cl->info
		, cl->main_krl.krl
		, 2
		, work_size) == CL_SUCCESS);
}
