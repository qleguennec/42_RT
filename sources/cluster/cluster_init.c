/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cluster_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 14:50:25 by qle-guen          #+#    #+#             */
/*   Updated: 2017/04/20 15:41:26 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cluster.h"
#include "parameters.h"

#define SEND(fd, msg) send(fd, msg, sizeof(msg) - 1, 0)

void
	*client_routine
	(void *arg)
{
	t_client	*self;
	int			nbytes;

	self = arg;
	nbytes = recv(self->fd, &self->capa, 4, 0);
	if (self->capa < CLIENT_MINCAPA || self->capa > CLIENT_MAXCAPA)
	{
		SEND(self->fd, "NOK");
		return (NULL);
	}
	write(1, "ok", 2);
	write(1, "\n", 1);
	SEND(self->fd, "OK");
	return (NULL);
}

void
	*accept_routine
	(void *arg)
{
	t_cluster	*self;

	self = arg;
	while (42)
	{
		self->clients[self->nclients].fd = accept(self->sockfd, NULL, NULL);
		pthread_create(&self->clients[self->nclients].thread
			, NULL
			, &client_routine
			, &self->clients[self->nclients]);
		self->nclients++;
	}
	return (NULL);
}

int
	cluster_init
	(t_cluster *cluster)
{
	struct sockaddr_in	self_addr;
	int					yes;

	ft_bzero(cluster, sizeof(*cluster));
	cluster->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	yes = 1;
	setsockopt(cluster->sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, 4);
	self_addr.sin_family = AF_INET;
	self_addr.sin_port = htons(CLUSTER_PORT);
	self_addr.sin_addr.s_addr = INADDR_ANY;
	bind(cluster->sockfd, (void *)&self_addr, sizeof(self_addr));
	listen(cluster->sockfd, CLUSTER_MAX_CLIENTS);
	pthread_create(&cluster->accept_thread, NULL, &accept_routine, cluster);
	return (0);
}
