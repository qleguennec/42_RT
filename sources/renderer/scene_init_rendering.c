/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_init_rendering.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 14:56:48 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/14 12:37:34 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "test_krl.h"
#include "libfmt.h"

bool
	scene_init_rendering
	(t_rt *rt
	, t_cl *cl)
{
	if (!cl_main_krl_init(cl))
		return (ERR("cannot init kernel", false, 0));
	if (!cl_main_krl_exec(cl, rt->scn))
		return (ERR("cannot exec kernel", false, 0));
	return (true);
}
