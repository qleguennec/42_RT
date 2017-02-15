/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_main_krl_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 12:07:51 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/15 17:07:31 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libfmt.h"

// TODO remove debug includes
#include <assert.h>

bool
	cl_main_krl_exec
	(t_cl *cl
	, t_scene *scn)
// TODO remove scn ptr from parameters
{
	int			ret;
	size_t		work_size[2];

	assert(cl->n_lgts == scn->n_lgts);
	assert(cl->n_objs == scn->n_objs);
	work_size[0] = WIN_W;
	work_size[1] = WIN_H;
	if ((ret = cl_krl_exec(&cl->info, cl->main_krl.krl, 2, work_size))
		!= CL_SUCCESS)
		return (ERR("cannot exec kernel, err %a", false, ret));
	return (true);
}
