/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_cam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 12:17:28 by qle-guen          #+#    #+#             */
/*   Updated: 2017/03/01 21:42:26 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_interface.h"
#include "obj_types.h"
#include "rt.h"

#define CPY(a) dest->a = src->a

void
	cpy_cam
	(t_cl_cam *dest
	, t_obj *src)
{
	ft_bzero(dest, sizeof(*dest));
	CPY(pos);
	CPY(rot);
	CPY(focal);
}
