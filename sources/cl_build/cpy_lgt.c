/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_lgt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 09:31:07 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/12 16:50:17 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_interface.h"
#include "rt.h"

// TODO remove debug includes
#include <assert.h>

#define CPY(a) cl_lgt->a = obj->a

void
	cpy_lgt
	(t_cl_lgt *cl_lgt
	, t_obj *obj)
{
	//assert(obj->type == 'L');
	CPY(pos);
	CPY(rot);
	CPY(intensity);
	CPY(shiness);
	CPY(mshiness);
}
