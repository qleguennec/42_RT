/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_copy_image_buffer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 16:35:42 by qle-guen          #+#    #+#             */
/*   Updated: 2017/05/08 11:25:33 by qle-guen         ###   ########.fr       */
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
	ssize_t nbytes;

	if (cl->cli_list)
	{
		printf("render\n");
		if ((nbytes = recv(cl->cli_list->fd
			, buffer, cl->main_krl.sizes[0], MSG_WAITALL))
			!= (ssize_t)cl->main_krl.sizes[0])
		{
			perror("recv");
			printf("%ld bytes received\n", nbytes);
			return (ERR("cannot receive image buffer from client"
				, false, 0));
		}
		printf("read %ld bytes\n", nbytes);
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
