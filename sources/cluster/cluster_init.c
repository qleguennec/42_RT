/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cluster_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 14:50:25 by qle-guen          #+#    #+#             */
/*   Updated: 2017/04/21 15:36:57 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cluster.h"
#include "parameters.h"

#define SEND(fd, msg) send(fd, msg, sizeof(msg) - 1, 0)

void
	*accept_routine
	(void *arg)
{
	t_cluster	*self;
	int			fd;
	t_client	*new;

	self = arg;
	while (42)
	{
		fd = accept(self->sockfd, NULL, NULL);
		new = malloc(sizeof(*new));
		new->fd = fd;
		new->next = self->cli_list;
		self->cli_list = new;
		cluster_send_command_all(self, "int", &fd, 4);
	}
	return (NULL);
}

int
	cluster_init
	(t_cluster *cluster)
{
	struct sockaddr_in	self_addr;

	ft_bzero(cluster, sizeof(*cluster));
	cluster->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(cluster->sockfd, SOL_SOCKET, SO_REUSEADDR, NULL, 4);
	self_addr.sin_family = AF_INET;
	self_addr.sin_port = htons(CLUSTER_PORT);
	self_addr.sin_addr.s_addr = INADDR_ANY;
	bind(cluster->sockfd, (void *)&self_addr, sizeof(self_addr));
	listen(cluster->sockfd, CLUSTER_MAX_CLIENTS);
	pthread_create(&cluster->accept_thread, NULL, &accept_routine, cluster);
	return (0);
}
