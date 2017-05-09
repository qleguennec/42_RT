/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_send_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 11:18:52 by qle-guen          #+#    #+#             */
/*   Updated: 2017/05/09 11:48:13 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cluster.h"
#include "../cl_build/cl_interface.h"

// TODO remove debug includes
# include <assert.h>

int
	cluster_send_command
	(t_client *client
	, char command
	, void *arg
	, size_t arg_size)
{
	char	ack;

	if (!send(client->fd, &command, 1, 0))
		return (0);
	if (!send(client->fd, &arg_size, 8, 0))
		return (0);
	if (arg_size)
	{
		if (!send(client->fd, arg, arg_size, 0))
			return (0);
	}
	if (recv(client->fd, &ack, 1, 0) == 0)
		return (0);
	if (ack == 'c')
		client->status |= CLIENT_CAM_OK;
	if (ack == 'l')
		client->status |= CLIENT_LGT_OK;
	if (ack == 'o')
		client->status |= CLIENT_OBJ_OK;
	return (1);
}

static void
	remove_client
	(t_cl *cl
	, t_client **cli
	, t_client **tmp)
{
	if (*tmp == NULL)
	{
		cl->cli_list = (*cli)->next;
		close((*cli)->fd);
		free(*cli);
		*cli = cl->cli_list;
	}
	else
	{
		(*tmp)->next = (*cli)->next;
		free(*cli);
		*cli = (*tmp)->next;
	}
}

void
	*dup_kernel_data
	(t_cl *cl
	, char cmd)
{
	void	*ret;
	size_t	size;

	ret = NULL;
	// TODO norm
	// TODO this is really bad
	if (cmd == 'c')
	{
		ret = malloc(sizeof(t_cl_cam));
		if (ret != NULL)
			cl_read(&cl->info, cl->main_krl.args[1], sizeof(t_cl_cam), ret);
	}
	if (cmd == 'l')
	{
		size = sizeof(t_cl_lgt) * cl->n_lgts;
		ret = malloc(size);
		if (ret != NULL)
			cl_read(&cl->info, cl->lgts, size, ret);
	}
	if (cmd == 'o')
	{
		size = sizeof(t_cl_obj) * cl->n_objs;
		ret = malloc(size);
		if (ret != NULL)
			cl_read(&cl->info, cl->objs, size, ret);
	}
	return (ret);
}

static int
	fill_client_buffers
	(t_cl *cl
	, t_client *cli)
{
	void	*buffer;
	int		alive;

	buffer = NULL;
	// TODO this is really really bad
	if ((cli->status & CLIENT_CAM_OK) == 0)
	{
		if (!(buffer = dup_kernel_data(cl, 'c')))
			return (0);
		alive = cluster_send_command(cli, 'c', buffer, sizeof(t_cl_cam));
	}
	if ((cli->status & CLIENT_OBJ_OK) == 0)
	{
		if (!(buffer = dup_kernel_data(cl, 'o')))
			return (0);
		alive = cluster_send_command(cli, 'o', buffer
			, cl->n_objs * sizeof(t_cl_obj));
	}
	if ((cli->status & CLIENT_LGT_OK) == 0)
	{
		if (!(buffer = dup_kernel_data(cl, 'l')))
			return (0);
		alive = cluster_send_command(cli, 'l', buffer
			, cl->n_lgts * sizeof(t_cl_lgt));
	}
	free(buffer);
	return (alive);
}

int
	cluster_send_command_all
	(t_cl *cl
	, char command
	, void *arg
	, size_t arg_size)
{
	t_client	*cli;
	t_client	*tmp;
	int			nclients;
	int			alive;

	tmp = NULL;
	nclients = 0;
	cli = cl->cli_list;
	while (cli != NULL)
	{
		if (command == 'r')
			alive = fill_client_buffers(cl, cli);
		if (alive)
			alive = cluster_send_command(cli, command, arg, arg_size);
		if (!alive)
			remove_client(cl, &cli, &tmp);
		else
		{
			tmp = cli;
			cli = cli->next;
			nclients++;
		}
		printf("alive: %d command: %c\n", alive, command);
	}
	return (nclients);
}
