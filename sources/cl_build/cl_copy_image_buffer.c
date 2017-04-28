/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_copy_image_buffer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 16:35:42 by qle-guen          #+#    #+#             */
/*   Updated: 2017/04/28 13:03:52 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libfmt.h"
#include <sys/socket.h>

bool
	cl_copy_image_buffer
	(t_cl *cl
	, void *buffer)
{
	int		ret;

	if (cl->cli_list)
	{
		printf("render\n");
		if (recv(cl->sockfd, buffer, cl->main_krl.sizes[0], 0) <= 0)
			return (ERR("cannot receive image buffer from client"
				, false, 0));
	}
	else
	{
		if ((ret = cl_read(&cl->info
			, cl->main_krl.args[0]
			, cl->main_krl.sizes[0]
			, buffer))
			!= CL_SUCCESS)
			return (ERR("cannot copy image buffer, err %a", false, ret));
	}
	return (true);
}
