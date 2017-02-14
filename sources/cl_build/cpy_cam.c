/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_cam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 12:17:28 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/13 12:23:30 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_interface.h"
#include "obj_type.h"
#include "rt.h"

// TODO remove debug includes
#include <assert.h>

#define CPY(a) dest->a = src->a

void
	cpy_cam
	(t_cl_cam *dest
	, t_obj *src)
{
	CPY(pos);
	CPY(rot);
	CPY(focal);
}
