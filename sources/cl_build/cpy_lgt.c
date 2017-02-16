/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_lgt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 09:31:07 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/16 12:18:43 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_interface.h"
#include "rt.h"

// TODO remove debug includes
#include <assert.h>

#define CPY(a) dest->a = src->a

void
	cpy_lgt
	(t_cl_lgt *dest
	, t_obj *src)
{
	//assert(src->type == 'L');
	CPY(pos);
	CPY(rot);
	CPY(clr);
	CPY(intensity);
}
