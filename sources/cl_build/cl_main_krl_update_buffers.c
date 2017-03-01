/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_main_krl_update_buffers.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 08:51:33 by qle-guen          #+#    #+#             */
/*   Updated: 2017/03/01 21:48:04 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
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

	if (cl->n_lgts)
		clReleaseMemObject(cl->lgts);
	while (n)
	{
		if (lgts->visibility)
		{
			cpy_lgt(&lgt_tmp, lgts);
			VECT_ADD(buf, lgt_tmp);
		}
		n--;
		lgts = lgts->next;
	}
	if (!(cl->n_lgts = buf->used / sizeof(lgt_tmp)))
		return (true);
	cl->lgts = clCreateBuffer(cl->info.ctxt, 0, buf->used, NULL, &ret);
	if (ret != CL_SUCCESS)
		return (ERR("cannot create buffer for lgts, err %a", false, ret));
	if (!((ret = CL_KRL_ARG(cl->main_krl.krl, 3, cl->lgts)) == CL_SUCCESS
	&& (ret = CL_KRL_ARG(cl->main_krl.krl, 5, cl->n_lgts)) == CL_SUCCESS))
		return (ERR("cannot set lgts & n_lgts args in kernel, err %a",
		false, ret));
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

	if (cl->n_objs)
		clReleaseMemObject(cl->objs);
	while (n)
	{
		if (objs->visibility)
		{
			cpy_obj(&obj_tmp, objs);
			VECT_ADD(buf, obj_tmp);
		}
		n--;
		objs = objs->next;
	}
	if (!(cl->n_objs = buf->used / sizeof(obj_tmp)))
		return (true);
	cl->objs = clCreateBuffer(cl->info.ctxt, 0, buf->used, NULL, &ret);
	if (ret != CL_SUCCESS)
		return (ERR("cannot create buffer for objs, err %a", false, ret));
	if (!((ret = CL_KRL_ARG(cl->main_krl.krl, 2, cl->objs)) == CL_SUCCESS
	&& (ret = CL_KRL_ARG(cl->main_krl.krl, 4, cl->n_objs)) == CL_SUCCESS))
		return (ERR("cannot set objs & n_objs args in kernel, err %a",
		false, ret));
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
		if (buf.used && (ret =
			cl_write(&cl->info, cl->lgts, buf.used, buf.data)) != CL_SUCCESS)
			return (ERR("cannot write to light buffer, err %a", false, ret));
		buf.used = 0;
	}
	if (cl->n_objs != scene->n_objs)
	{
		if (!krl_update_objs(cl, &buf, scene->b_objs->next, scene->n_objs))
			return (false);
		if (buf.used && (ret =
			cl_write(&cl->info, cl->objs, buf.used, buf.data)) != CL_SUCCESS)
			return (ERR("cannot write to object buffer, err %a", false, ret));
	}
	if (buf.data)
		free(buf.data);
	return (true);
}
