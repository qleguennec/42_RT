/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_copy_image_buffer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 16:35:42 by qle-guen          #+#    #+#             */
/*   Updated: 2017/05/10 10:45:19 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libfmt.h"
#include <sys/socket.h>

static bool
	buffer_aggregate_samples
	(t_cl *cl
	, void *buffer
	, int nsamples)
{
	size_t		i;
	t_client	*cli;
	int			ret;

	ret = 0;
	cli = cl->cli_list;
	i = 0;
	while (i < cl->main_krl.sizes[0])
	{
		if (cli)
		{
			ft_memcpy((char *)buffer + i, &(((char *)cli->buffer)[i])
				, cl->main_krl.sizes[0] / nsamples);
			cli = cli->next;
		}
		else
		{
			clFinish(cl->info.cmd_queue);
			if ((ret = clEnqueueReadBuffer(cl->info.cmd_queue
				, cl->main_krl.args[0], CL_TRUE, i
				, cl->main_krl.sizes[0] / nsamples
				, buffer + i, 0, NULL, NULL)) != CL_SUCCESS)
				return (ERR("cannot copy image buffer, err %a", false, ret));
		}
		i += cl->main_krl.sizes[0] / nsamples;
	}
	assert(cli == NULL);
	assert(i == cl->main_krl.sizes[0]);
	return (true);
}

bool
	cl_copy_image_buffer
	(t_cl *cl
	, void *buffer)
{
	int			nsamples;
	t_client	*cli;

	nsamples = 1;
	cli = cl->cli_list;
	while (cli)
	{
		nsamples++;
		cli = cli->next;
	}
	return (buffer_aggregate_samples(cl, buffer, nsamples));
}
