/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 09:31:07 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/12 16:51:16 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_interface.h"
#include "obj_type.h"
#include "rt.h"

// TODO remove debug includes
#include <assert.h>


#define CPY(a) cl_obj->a = obj->a

void
	cpy_obj
	(t_cl_obj *cl_obj
	, t_obj *obj)
{
	//assert(obj->type == 'O');
	obj->type = TYPE_SPHERE;
	CPY(type);
	CPY(pos);
	CPY(rot);
	CPY(clr);
	CPY(opacity);
	CPY(width);
	CPY(radius);
	CPY(width);
	CPY(height);
	CPY(specolor);
	CPY(reflex);
	CPY(refract);
}
