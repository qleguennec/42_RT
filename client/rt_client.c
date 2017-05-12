/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 09:18:16 by qle-guen          #+#    #+#             */
/*   Updated: 2017/04/26 14:48:50 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_client.h"

#define DIGIT "0123456789"

#define MINPORT 100
#define MAXPORT 200000
#define MINCAPA 100
#define MAXCAPA 10000000

static int
	usage
	(int ret)
{
	static char	usage[] = "usage: rt-client IP:PORT\n";
	static char	port_range[] = "PORT must be between %a and %a\n";

	fmt_print(1, 0, usage, sizeof(usage) - 1);
	fmt_print(1, 0, port_range, sizeof(port_range) - 1, MINPORT, MAXPORT);
	return (ret);
}

static int
	get_host_info
	(char *arg
	, char **host_ip
	, int *port)
{
	unsigned long	port_arg;
	char			*port_str;

	port_arg = 0;
	if ((port_str = ft_strchr(arg, ':')) == NULL)
		return (0);
	port_arg = 0;
	STRTOB10(port_str + 1, port_arg);
	if (port_arg < MINPORT || port_arg > MAXPORT)
		return (0);
	*port = port_arg;
	*host_ip = malloc(1 + port_str - arg);
	ft_memcpy(*host_ip, arg, port_str - arg);
	(*host_ip)[port_str - arg] = '\0';
	return (1);
}

int
	main
	(int argc
	, char **argv)
{
	int		port;
	int		sockfd;
	char	*host_ip;
	t_vect	data;
	t_cl	cl;

	if (argc != 2)
		return (usage(1));
	if (!get_host_info(argv[1], &host_ip, &port))
		return (usage(2));
	sockfd = client_init(host_ip, port);
	if (sockfd <= 0)
		return (0);
	vect_init(&data);
	cl_main_krl_init(&cl);
	client_loop(sockfd, &data, &cl);
	return (0);
}
