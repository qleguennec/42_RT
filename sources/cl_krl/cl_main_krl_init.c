/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_main_krl_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 15:08:54 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/10 10:58:11 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl.h"
#include "libvect.h"
#include "libfmt.h"
#include "parameters.h"

#define FILENAME	"main.cl"
#define KRLNAME		"main"

static void
	cl_build_line
	(t_vect *build_line)
{
	vect_init(build_line);
	VECT_STRADD(build_line, "rt_ray_send:");
	VECT_STRADD(build_line, "-I sources/cl ");
	FMT_VECT(build_line, "-D WIDTH=%a ", WIN_W);
	FMT_VECT(build_line, "-D HEIGHT=%a ", WIN_H);
	FMT_VECT(build_line, "-D AREA=%a ", WIN_W * WIN_H);
	FMT_VECT(build_line, "-D XCENTER=%a ", WIN_W / 2);
	FMT_VECT(build_line, "-D YCENTER=%a ", WIN_H / 2);
}

bool
	cl_main_krl_init
	(t_cl *cl)
{
	int		fd;
	t_vect	build_line;

	if ((fd = open(FILENAME, O_RDONLY)) < 0)
		return (false);
	cl_init(&cl->info);
	cl_krl_init(&cl->main_krl, 1);
	cl->main_krl.sizes[0] = WIN_W * WIN_H * sizeof(int);
	cl_build_line(&build_line);
	if (cl_krl_build(&cl->info
		, &cl->main_krl
		, fd
		, &build_line) != CL_SUCCESS)
		return (false);
	close(fd);
	free(build_line.data);
	return (true);
}
