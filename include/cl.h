/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 15:06:29 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/11 15:36:32 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_H
# define CL_H

# include "libcl.h"
# include "rt.h"

typedef struct	s_cl
{
	t_cl_info	info;
	t_cl_krl	main_krl;
	cl_mem		objs;
	cl_mem		lgts;
	short		n_objs;
	short		n_lgts;
}				t_cl;

bool			cl_test_krl(t_rt *rt);

/*
** needs to be call once at the start of the program
*/
bool			cl_main_krl_init(t_cl *cl);

/*
** needs to be call each time the scene needs to be rendered
*/
bool			cl_main_krl_exec(t_cl *cl, t_scene *scene);

/*
** needs to be call each time the camera is changed
** AND at the start of the program after
** cl_main_krl_init
*/
bool			cl_main_krl_update_camera(t_cl *cl, t_obj *obj);

#endif
