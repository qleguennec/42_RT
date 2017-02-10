/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_krl_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 12:07:51 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/10 08:34:50 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static bool
	cl_update_objs
	(t_cl *cl
	, t_vect *objs)
{
	t_i32	ret;

	if (objs->used / sizeof(t_obj) == cl->nobjs)
		return (true);
	if (cl->nobjs)
		clReleaseMemObject(cl->objs);
	cl->nobjs = objs->used / sizeof(t_obj);
	cl->objs = clCreateBuffer(cl->info.ctxt, 0, objs->used, NULL, &ret);
	if (ret != CL_SUCCESS)
		return (false);
	if (cl_write(&cl->info, cl->objs, objs->used, objs->data) != CL_SUCCESS)
		return (false);
	return (CL_KRL_ARG(cl->ray_send_krl.krl, 1, cl->objs) == CL_SUCCESS
		&& CL_KRL_ARG(cl->ray_send_krl.krl, 2, cl->nobjs) == CL_SUCCESS);
}

bool
	cl_krl_exec
	(t_cl *cl)
{
	size_t		work_size[2];
	t_cl		*cl;
	t_scene		*scene;

	cl = &rt->cl;
	scene = &rt->scene;
	if (!cl_update_objs(cl, &scene->objs))
		return (false);
	work_size[0] = rt->size.x;
	work_size[1] = rt->size.y;
	return (cl_krl_exec(&cl->info
		, cl->ray_send_krl.krl
		, 2
		, work_size) == CL_SUCCESS);
}
