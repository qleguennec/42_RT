/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_main_krl_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 12:07:51 by qle-guen          #+#    #+#             */
/*   Updated: 2017/03/01 16:46:57 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libfmt.h"

// TODO remove debug includes
#include <assert.h>

#define N_BENCH 2000

static double
	main_krl_exec_benchmark
	(t_cl *cl
	, size_t *work_size)
{
	cl_event	ev;
	cl_ulong	end;
	cl_ulong	start;
	int			ret;

	ret = clEnqueueNDRangeKernel(cl->info.cmd_queue
		, cl->main_krl.krl, 2, NULL, work_size, NULL, 0, NULL, &ev);
	clWaitForEvents(1, &ev);
	clFinish(cl->info.cmd_queue);
	clGetEventProfilingInfo(ev, CL_PROFILING_COMMAND_START
		, sizeof(start), &start, NULL);
	clGetEventProfilingInfo(ev, CL_PROFILING_COMMAND_END
		, sizeof(end), &end, NULL);
	return ((end - start) / 1000000000.0);
}

static void
	handle_null_buffers
	(t_cl *cl)
{
	cl_short	ns;
	cl_mem		nm;

	ns = 0;
	nm = 0;
	if (cl->n_lgts == 0)
	{
		CL_KRL_ARG(cl->main_krl.krl, 5, ns);
		CL_KRL_ARG(cl->main_krl.krl, 3, nm);
	}
	if (cl->n_objs == 0)
	{
		CL_KRL_ARG(cl->main_krl.krl, 4, ns);
		CL_KRL_ARG(cl->main_krl.krl, 2, nm);
	}
}

bool
	cl_main_krl_exec
	(t_cl *cl)
{
	double		total;
	int			ret;
	size_t		i;
	size_t		work_size[2];

	work_size[0] = REND_W;
	work_size[1] = REND_H;
	handle_null_buffers(cl);
	if (BENCHMARK_KRL == 1)
	{
		i = -1;
		total = 0;
		while (++i < N_BENCH)
			total += main_krl_exec_benchmark(cl, work_size);
		total /= N_BENCH;
		printf("render time: %lfs ", total);
		printf("fps: %lf\n", 1.0 / total);
	}
	else
	{
		if ((ret = cl_krl_exec(&cl->info, cl->main_krl.krl, 2, work_size))
			!= CL_SUCCESS)
			return (ERR("cannot exec kernel, err %a\n", false, ret));
	}
	return (true);
}
