/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_send_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 11:18:52 by qle-guen          #+#    #+#             */
/*   Updated: 2017/04/21 16:20:04 by qle-guen         ###   ########.fr       */
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
	int	ok;

	if (!send(client->fd, command, ft_strlen(command), 0))
		return (0);
	if (!send(client->fd, &arg_size, 8, 0))
		return (0);
	if (!send(client->fd, arg, arg_size, 0))
		return (0);
	if (!recv(client->fd, &ok, 4, 0))
		return (0);
	return (ok);
}

static void
	remove_client
	(t_cluster *cluster
	, t_client **cli
	, t_client **tmp)
{
	if (*tmp == NULL)
	{
		cluster->cli_list = (*cli)->next;
		close((*cli)->fd);
		free(*cli);
		*cli = cluster->cli_list;
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
	(t_cluster *cluster
	, char *command
	, void *arg
	, size_t arg_size)
{
	t_client	*cli;
	t_client	*tmp;
	int			nclients;

	tmp = NULL;
	cli = cluster->cli_list;
	nclients = 0;
	while (cli != NULL)
	{
		if (!cluster_send_command(cli, command, arg, arg_size))
			remove_client(cluster, &cli, &tmp);
		else
		{
			tmp = cli;
			cli = cli->next;
			nclients++;
		}
	}
	return (nclients);
}
