/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cluster_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 14:50:25 by qle-guen          #+#    #+#             */
/*   Updated: 2017/04/26 16:43:31 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cluster.h"
#include "parameters.h"

#define SEND(fd, msg) send(fd, msg, sizeof(msg) - 1, 0)

void
	*accept_routine
	(void *arg)
{
	t_cl		*self;
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
	}
	return (NULL);
}

int
	cluster_init
	(t_cl *cl)
{
	struct sockaddr_in	self_addr;

	cl->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(cl->sockfd, SOL_SOCKET, SO_REUSEADDR, NULL, 4);
	self_addr.sin_family = AF_INET;
	self_addr.sin_port = htons(CLUSTER_PORT);
	self_addr.sin_addr.s_addr = INADDR_ANY;
	bind(cl->sockfd, (void *)&self_addr, sizeof(self_addr));
	listen(cl->sockfd, CLUSTER_MAX_CLIENTS);
	pthread_create(&cl->accept_thread, NULL, &accept_routine, cl);
	return (0);
}
