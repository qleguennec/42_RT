/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_cam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 12:17:28 by qle-guen          #+#    #+#             */
/*   Updated: 2017/05/12 14:51:38 by qle-guen         ###   ########.fr       */
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
	if (ft_strlcmp((void *)src->n, "skyday") == 0)
		dest->skytype = CAM_SKYDAY;
	else if (ft_strlcmp((void *)src->n, "skynight") == 0)
		dest->skytype = CAM_SKYDAY;
	else
		dest->skytype = CAM_OTHER;
	CPY(pos);
	CPY(rot);
	CPY(focal);
}
