/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_send_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 11:18:52 by qle-guen          #+#    #+#             */
/*   Updated: 2017/04/27 17:07:12 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cluster.h"

// TODO remove debug includes
# include <assert.h>

int
	cluster_send_command
	(t_client *client
	, char *command
	, void *arg
	, size_t arg_size)
{
	if (!send(client->fd, command, ft_strlen(command), 0))
		return (0);
	if (!send(client->fd, &arg_size, 8, 0))
		return (0);
	if (arg_size)
	{
		if (!send(client->fd, arg, arg_size, 0))
			return (0);
	}
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

int
	cluster_send_command_all
	(t_cl *cl
	, char *command
	, void *arg
	, size_t arg_size)
{
	t_client	*cli;
	t_client	*tmp;
	int			nclients;

	tmp = NULL;
	cli = cl->cli_list;
	nclients = 0;
	while (cli != NULL)
	{
		if (!cluster_send_command(cli, command, arg, arg_size))
			remove_client(cl, &cli, &tmp);
		else
		{
			tmp = cli;
			cli = cli->next;
			nclients++;
		}
	}
	return (nclients);
}
