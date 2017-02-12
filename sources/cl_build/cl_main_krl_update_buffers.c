/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_main_krl_update_buffers.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 08:51:33 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/12 16:27:02 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "cl.h"
#include "cl_interface.h"
#include "libvect.h"
#include "libcl.h"

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
	size_t		i;

	if (n == cl->n_lgts)
		return (true);
	if (cl->n_lgts)
		clReleaseMemObject(cl->lgts);
	cl->lgts = clCreateBuffer(cl->info.ctxt, 0, n * sizeof(t_cl_obj), NULL
		, &ret);
	if (ret != CL_SUCCESS)
		return (false);
	cl->n_lgts = n;
	if (!(CL_KRL_ARG(cl->main_krl.krl, 2, cl->lgts) == CL_SUCCESS
		&& CL_KRL_ARG(cl->main_krl.krl, 5, cl->n_lgts) == CL_SUCCESS))
		return (false);
	vect_req(buf, n * sizeof(t_cl_lgt));
	i = 0;
	while (lgts)
	{
		cpy_lgt(((t_cl_lgt *)buf->data) + i++, lgts);
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
	size_t		i;

	if (n == cl->n_objs)
		return (true);
	if (cl->n_objs)
		clReleaseMemObject(cl->objs);
	cl->objs = clCreateBuffer(cl->info.ctxt, 0
		, n * sizeof(t_cl_obj), NULL, &ret);
	if (ret != CL_SUCCESS)
		return (false);
	cl->n_objs = n;
	if (!(CL_KRL_ARG(cl->main_krl.krl, 1, cl->objs) == CL_SUCCESS
		&& CL_KRL_ARG(cl->main_krl.krl, 4, cl->n_objs) == CL_SUCCESS))
		return (false);
	vect_req(buf, n * sizeof(t_cl_obj));
	i = 0;
	while (objs)
	{
		cpy_obj(((t_cl_obj *)buf->data) + i++, objs);
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
