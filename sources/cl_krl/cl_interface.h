/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_interface.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 07:55:11 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/10 10:18:33 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_INTERFACE_H
# define CL_INTERFACE_H

#include <OpenCL/opencl.h>
#include "rt.h"
#include "cl.h"

typedef struct		s_cl_obj
{
	cl_short		type;
	cl_float3		pos;
	cl_float3		rot;
	cl_float3		clr;
	cl_float		opacity;
	cl_float		width;
	cl_float		height;
	cl_float		radius;
	cl_float		specolor;
	cl_float		reflex;
	cl_float		refract;
}					t_cl_obj;

typedef struct		s_cl_lgt
{
	cl_float3		pos;
	cl_float3		rot;
	cl_float		intensity;
	cl_float		shiness;
	cl_float		mshiness;
}					t_cl_lgt;

bool		cl_main_krl_update_buffers(t_cl *cl, t_scene *scene);

/*
** implementation of these two functions needs to be reviewed
** each time data structures are modified
*/

void		cpy_lgt(t_cl_lgt *cl_obj, t_obj *obj);
void		cpy_obj(t_cl_obj *cl_obj, t_obj *obj);

#endif
