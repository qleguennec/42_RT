/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 15:06:29 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/10 08:36:28 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_H
# define CL_H

# include "libcl.h"

typedef struct	s_cl
{
	t_cl_info	info;
	t_cl_krl	ray_send_krl;
	cl_mem		objs;
	size_t		nobjs;
}				t_cl;

int				cl_krl_init(t_cl *cl);
int				cl_krl_exec(t_cl *cl);

#endif
