/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_main_krl_update_buffers.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 08:51:33 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/18 12:16:51 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "cl_interface.h"
#include "libvect.h"
#include "libcl.h"
#include "libfmt.h"

// TODO remove debug includes
#include <assert.h>

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
	if (!((ret = CL_KRL_ARG(cl->main_krl.krl, 3, cl->lgts)) == CL_SUCCESS
		&& (ret = CL_KRL_ARG(cl->main_krl.krl, 5, n)) == CL_SUCCESS))
		return (ERR("cannot set lgts & n_lgts args in kernel, err %a"
			, false, ret));
	cl->n_lgts = 0;
	while (cl->n_lgts < n)
	{
		cpy_lgt(&lgt_tmp, lgts);
		VECT_ADD(buf, lgt_tmp);
		lgts = lgts->next;
		cl->n_lgts++;
	}
	return (true);
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
	if (!((ret = CL_KRL_ARG(cl->main_krl.krl, 2, cl->objs)) == CL_SUCCESS
		&& (ret = CL_KRL_ARG(cl->main_krl.krl, 4, n)) == CL_SUCCESS))
		return (ERR("cannot set objs & n_objs args in kernel, err %a"
			, false, ret));
	cl->n_objs = 0;
	while (cl->n_objs < n)
	{
		cpy_obj(&obj_tmp, objs);
		VECT_ADD(buf, obj_tmp);
		objs = objs->next;
		cl->n_objs++;
	}
	return (true);
}

bool
	cl_main_krl_update_buffers
	(t_cl *cl
	, t_scene *scene)
{
	int		ret;
	t_vect	buf;

	assert(cl->main_krl.sizes[1] == sizeof(t_cl_cam));
	vect_init(&buf);
	if (cl->n_lgts != scene->n_lgts)
	{
		if (!krl_update_lgts(cl, &buf, scene->b_lgts->next, scene->n_lgts))
			return (false);
		assert(scene->n_lgts == buf.used / sizeof(t_cl_lgt));
		if ((ret = cl_write(&cl->info, cl->lgts, buf.used, buf.data))
			!= CL_SUCCESS)
			return (ERR("cannot write to light buffer, err %a", false, ret));
		buf.used = 0;
	}
	if (cl->n_objs != scene->n_objs)
	{
		if (!krl_update_objs(cl, &buf, scene->b_objs->next, scene->n_objs))
			return (false);
		assert(scene->n_objs == buf.used / sizeof(t_cl_obj));
		if ((ret = cl_write(&cl->info, cl->objs, buf.used, buf.data))
			!= CL_SUCCESS)
			return (ERR("cannot write to object buffer, err %a", false, ret));
	}
	if (buf.data)
		free(buf.data);
	return (true);
}
