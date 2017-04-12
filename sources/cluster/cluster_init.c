/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cluster_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 14:50:25 by qle-guen          #+#    #+#             */
/*   Updated: 2017/04/12 17:22:36 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cluster.h"
#include "parameters.h"

int
	cluster_init
	(t_cluster *cluster)
{
	struct sockaddr_in	sin;

	ft_bzero(cluster, sizeof(*cluster));
	cluster->timeout.tv_sec = 2;
	cluster->timeout.tv_usec = 0;
	FD_ZERO(&cluster->fdset);
	cluster->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	FD_SET(cluster->sockfd, &cluster->fdset);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(CLUSTER_PORT);
	sin.sin_addr.s_addr = INADDR_ANY;
	listen(cluster->sockfd, 128);
	return (cluster->sockfd);
}
