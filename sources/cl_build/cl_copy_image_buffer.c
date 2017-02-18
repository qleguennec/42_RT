/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_copy_image_buffer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 16:35:42 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/15 09:46:08 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libfmt.h"

bool
	cl_copy_image_buffer
	(t_cl *cl
	, void *buffer)
{
	int		ret;

	if ((ret = cl_read(&cl->info
		, cl->main_krl.args[0]
		, cl->main_krl.sizes[0]
		, buffer))
		!= CL_SUCCESS)
		return (ERR("cannot copy image buffer, err %a", false, ret));
	return (true);
}
