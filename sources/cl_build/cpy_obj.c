/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 09:31:07 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/18 12:12:33 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_interface.h"
#include "obj_types.h"
#include "rt.h"

// TODO remove debug includes
#include <assert.h>

#define CPY(a) dest->a = src->a

void
	cpy_obj
	(t_cl_obj *dest
	, t_obj *src)
{
	assert(src->type == 'O');
	ft_bzero(dest, sizeof(*dest));
	dest->type = src->forme;
	/*
	CPY(pos);
	CPY(rot);
	CPY(clr);
	*/
	dest->pos.x = src->pos.x;
	dest->pos.y = src->pos.y;
	dest->pos.z = src->pos.z;
	dest->rot.x = src->rot.x;
	dest->rot.y = src->rot.y;
	dest->rot.z = src->rot.z;
	dest->clr.x = src->clr.x;
	dest->clr.y = src->clr.y;
	dest->clr.z = src->clr.z;
	/*
	CPY(opacity);
	CPY(width);
	CPY(height);
	CPY(radius);
	CPY(specolor);
	CPY(reflex);
	CPY(refract);
	CPY(shiness);
	CPY(mshiness);
	*/
}
