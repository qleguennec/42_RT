/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cluster_listen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 15:41:24 by qle-guen          #+#    #+#             */
/*   Updated: 2017/04/12 17:19:35 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cluster.h"

int
	cluster_listen
	(t_cluster *cluster)
{
	int		sel;

	sel = select(cluster->sockfd + 1
		, &cluster->fdset, NULL, NULL, &cluster->timeout);
	printf("sel=%d\n", sel);
	return (0);
}
