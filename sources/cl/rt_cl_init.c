/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cl_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 15:08:54 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/09 15:53:44 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl.h"
#include "libvect.h"
#include "libfmt.h"

#define FILENAME	"rt_ray_send.cl"
#define KRLNAME		"rt_ray_send"

#define WIDTH		1
#define HEIGHT		1

static void
	cl_build_line
	(t_vect *build_line)
{
	vect_init(build_line);
	VECT_STRADD(build_line, "rt_ray_send:");
	VECT_STRADD(build_line, "-I. ");
	FMT_VECT(build_line, "-D WIDTH=%a ", WIN_W);
	FMT_VECT(build_line, "-D HEIGHT=%a ", WIN_H);
	FMT_VECT(build_line, "-D AREA=%a ", WIN_W * WIN_H);
	FMT_VECT(build_line, "-D XCENTER=%a ", WIN_W / 2);
	FMT_VECT(build_line, "-D YCENTER=%a ", WIN_H / 2);
}

int
	rt_cl_init
	(t_cl *cl)
{
	int		fd;
	t_vect	build_line;

	cl = &rt->cl;
	if ((fd = open(FILENAME, O_RDONLY)) < 0)
		return (0);
	cl_init(&cl->info);
	cl_krl_init(&cl->ray_send_krl, 1);
	cl->ray_send_krl.sizes[0] = WIDTH * HEIGHT * sizeof(int);
	cl_build_line(rt, &build_line);
	if (cl_krl_build(&cl->info
		, &cl->ray_send_krl
		, fd
		, &build_line) != CL_SUCCESS)
		return (0);
	close(fd);
	free(build_line.data);
	return (0);
}
