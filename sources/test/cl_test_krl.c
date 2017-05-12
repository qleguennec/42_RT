/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_test_krl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 11:00:05 by qle-guen          #+#    #+#             */
/*   Updated: 2017/03/01 21:42:48 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cl_build/cl_interface.h"
#include "test_krl.h"
#include "libvect.h"
#include "libfmt.h"
#include "parameters.h"
#include "obj_types.h"

#include <stdlib.h>
#include <limits.h>

#define FILENAME	"sources/test/test.cl"
#define KRLNAME		"test"

static bool
	test_krl_init
	(t_cl_krl *krl
	, t_vect *build_line)
{
	vect_init(build_line);
	VECT_STRADD(build_line, KRLNAME ":");
	VECT_STRADD(build_line, "-I sources/cl ");
	FMT_VECT(build_line, "-D WIDTH=%a ", WIN_W);
	FMT_VECT(build_line, "-D HEIGHT=%a ", WIN_H);
	FMT_VECT(build_line, "-D AREA=%a ", WIN_W * WIN_H);
	FMT_VECT(build_line, "-D XCENTER=%a ", WIN_W / 2);
	FMT_VECT(build_line, "-D YCENTER=%a ", WIN_H / 2);
	PRINT(FILENAME ":", 0);
	VECHO(build_line);
	cl_krl_init(krl, 2);
	krl->sizes[0] = sizeof(cl_uint);
	krl->sizes[1] = sizeof(t_cl_cam);
	return (true);
}

static bool
	test_krl_build
	(t_cl_info *info
	, t_cl_krl *test_krl
	, t_vect *build_line)
{
	int			fd;
	int			ret;

	if ((fd = open(FILENAME, O_RDONLY)) < 0)
		return (ERR("cannot open file " FILENAME, false, 0));
	if ((ret = cl_krl_build(info, test_krl, fd, build_line)) != CL_SUCCESS)
		return (ERR("cannot build kernel, err %a", false, ret));
	close(fd);
	free(build_line->data);
	return (true);
}

bool
	cl_test_krl
	(t_cl *cl
	, t_scene *scn)
{
	cl_int		ret;
	size_t		work_size;
	t_vect		build_line;

	cl_init(&cl->info);
	if (!test_krl_init(&cl->main_krl, &build_line))
		return (ERR("failed to init kernel", false, 0));
	if (!test_krl_build(&cl->info, &cl->main_krl, &build_line))
		return (ERR("cannot build kernel", false, 0));
	if (!cl_main_krl_update_camera(cl, scn->c_cam))
		return (ERR("cannot update camera", false, 0));
	if (!cl_main_krl_update_buffers(cl, scn))
		return (ERR("cannot update buffers", false, 0));
	work_size = 1;
	if ((ret = cl_krl_exec(&cl->info, cl->main_krl.krl, 1, &work_size))
		!= CL_SUCCESS)
		return (ERR("cannot execute kernel, opencl error %a", false, ret));
	return (clFinish(cl->info.cmd_queue) == CL_SUCCESS);
}
