/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_main_krl_update_buffers.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 08:51:33 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/13 12:26:03 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "cl.h"
#include "cl_interface.h"
#include "libvect.h"
#include "libcl.h"
#include "libfmt.h"

/*
** updates GPU memory
** needs to be called each time the scene is changed
*/

static bool
	krl_update_lgts
	(t_cl *cl
	, t_vect *buf
	, t_obj *lgts
	, short n)
{
	int			ret;
	t_cl_lgt	lgt_tmp;

	if (n == cl->n_lgts)
		return (true);
	if (cl->n_lgts)
		clReleaseMemObject(cl->lgts);
	cl->lgts = clCreateBuffer(cl->info.ctxt, 0
		, n * sizeof(t_cl_lgt), NULL, &ret);
	if (ret != CL_SUCCESS)
		return (ERR("cannot create buffer for lgts, err %a", false, ret));
	cl->n_lgts = n;
	if (!((ret = CL_KRL_ARG(cl->main_krl.krl, 3, cl->lgts)) == CL_SUCCESS
		&& (ret = CL_KRL_ARG(cl->main_krl.krl, 5, cl->n_lgts)) == CL_SUCCESS))
		return (ERR("cannot set lgts & n_lgts args in kernel, err %a"
			, false, ret));
	while (lgts)
	{
		cpy_lgt(&lgt_tmp, lgts);
		VECT_ADD(buf, lgt_tmp);
		lgts = lgts->next;
	}
	return (cl_write(&cl->info, cl->lgts, buf->used, buf->data)
		== CL_SUCCESS);
}

static bool
	krl_update_objs
	(t_cl *cl
	, t_vect *buf
	, t_obj *objs
	, short n)
{
	int			ret;
	t_cl_obj	obj_tmp;

	if (n == cl->n_objs)
		return (true);
	if (cl->n_objs)
		clReleaseMemObject(cl->objs);
	cl->objs = clCreateBuffer(cl->info.ctxt, 0
		, n * sizeof(t_cl_obj), NULL, &ret);
	if (ret != CL_SUCCESS)
		return (ERR("cannot create buffer for objs, err %a", false, ret));
	cl->n_objs = n;
	if (!((ret = CL_KRL_ARG(cl->main_krl.krl, 2, cl->objs)) == CL_SUCCESS
		&& (ret = CL_KRL_ARG(cl->main_krl.krl, 4, cl->n_objs)) == CL_SUCCESS))
		return (ERR("cannot set lgts & n_lgts args in kernel, err %a"
			, false, ret));
	while (objs)
	{
		cpy_obj(&obj_tmp, objs);
		VECT_ADD(buf, obj_tmp);
		objs = objs->next;
	}
	return (cl_write(&cl->info, cl->objs, buf->used, buf->data)
		== CL_SUCCESS);
}

bool
	cl_main_krl_update_buffers
	(t_cl *cl
	, t_scene *scene)
{
	t_vect	buf;

	vect_init(&buf);
	if (!krl_update_lgts(cl, &buf, scene->b_lgts, scene->n_lgts))
		return (false);
	buf.used = 0;
	if (!krl_update_objs(cl, &buf, scene->b_objs, scene->n_objs))
		return (false);
	free(buf.data);
	return (true);
}
