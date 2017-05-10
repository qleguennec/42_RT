/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_copy_image_buffer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 16:35:42 by qle-guen          #+#    #+#             */
/*   Updated: 2017/05/10 15:26:21 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libfmt.h"
#include <sys/socket.h>

/*
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
	while (42)
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
			printf("%lu %lu\n", i, cl->main_krl.sizes[0] / nsamples);
			break ;
		}
		i += cl->main_krl.sizes[0] / nsamples;
	}
	assert(cli == NULL);
	return (true);
}
*/

static bool
	buffer_average_samples
	(t_cl *cl
	, int *buffer
	, int nsamples)
{
	unsigned int	channels[4];
	size_t			i;
	t_client		*cli;

	i = 0;
	while (i < REND_W * REND_H)
	{
		ft_bzero(channels, sizeof(channels));
		cli = cl->cli_list;
		while (cli)
		{
			channels[0] += (cli->buffer[i] >> 0) & 0xFF;
			channels[1] += (cli->buffer[i] >> 8) & 0xFF;
			channels[2] += (cli->buffer[i] >> 16) & 0xFF;
			channels[3] += (cli->buffer[i] >> 24) & 0xFF;
			cli = cli->next;
		}
		channels[0] += (buffer[i] >> 0) & 0xFF;
		channels[1] += (buffer[i] >> 8) & 0xFF;
		channels[2] += (buffer[i] >> 16) & 0xFF;
		channels[3] += (buffer[i] >> 24) & 0xFF;
		channels[0] /= nsamples;
		channels[1] /= nsamples;
		channels[2] /= nsamples;
		channels[3] /= nsamples;
		/*
		assert(!printf("%u\n", channels[0]) || channels[0] <= 0xFF);
		assert(!printf("%u\n", channels[1]) || channels[1] <= 0xFF);
		assert(!printf("%u\n", channels[2]) || channels[2] <= 0xFF);
		assert(!printf("%u\n", channels[3]) || channels[3] <= 0xFF);
		*/
		buffer[i] = 0;
		buffer[i] |= (channels[0]) << 0;
		buffer[i] |= (channels[1]) << 8;
		buffer[i] |= (channels[2]) << 16;
		buffer[i] |= (channels[3]) << 24;
		buffer[i] |= 0x000000FF;
		i++;
	}
	return (true);
}

bool
	cl_copy_image_buffer
	(t_cl *cl
	, void *buffer)
{
	int			nsamples;
	int			ret;
	t_client	*cli;

	ret = 0;
	nsamples = 1;
	cli = cl->cli_list;
	while (cli)
	{
		nsamples++;
		cli = cli->next;
	}
	if ((ret = clEnqueueReadBuffer(cl->info.cmd_queue
		, cl->main_krl.args[0], CL_TRUE, 0
		, cl->main_krl.sizes[0], buffer, 0, NULL, NULL)) != CL_SUCCESS)
		return (ERR("cannot read image buffer, err %a", false, ret));
	if (nsamples == 1)
		return (true);
	return (buffer_average_samples(cl, buffer, nsamples));
}
