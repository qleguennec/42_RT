/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 12:33:46 by qle-guen          #+#    #+#             */
/*   Updated: 2017/04/28 13:47:06 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_client.h"
#include <errno.h>

int
	client_init
	(char *host_ip
	, int port)
{
	int					sockfd;
	struct hostent		*host;
	struct sockaddr_in	sin;

	if ((host = gethostbyname(host_ip)) == NULL)
		return (ERR("cant get hostname", 0, 0));
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		return (ERR("cant load socket", 0, 0));
	sin.sin_family = AF_INET;
	sin.sin_port = port;
	sin.sin_addr = *((struct in_addr *)host->h_addr);
	if (connect(sockfd, (struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		perror("connect");
		return (ERR("cant connect to server", 0, 0));
	}
	return (sockfd);
}
