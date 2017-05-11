/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 09:31:07 by qle-guen          #+#    #+#             */
/*   Updated: 2017/05/11 18:05:29 by erodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_interface.h"
#include "obj_types.h"
#include "rt.h"

#define CPY(a) dest->a = src->a

void
	cpy_obj
	(t_cl_obj *dest
	, t_obj *src)
{
	assert(src->type == 'O');
	ft_bzero(dest, sizeof(*dest));
	dest->type = src->forme;
	CPY(pos);
	CPY(rot);
	CPY(clr);
	CPY(opacity);
	CPY(width);
	CPY(height);
	CPY(radius);
	CPY(specular);
	CPY(shader);
	CPY(reflex);
	CPY(refrac);
	CPY(shiness);
	CPY(mshiness);
}
