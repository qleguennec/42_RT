/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_init_rendering.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 14:56:48 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/13 15:08:00 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "test_krl.h"

bool
	scene_init_rendering
	(t_rt *rt
	, t_cl *cl)
{
	return (cl_test_krl(cl, rt->scn));
}
