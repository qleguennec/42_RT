/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cl_interface.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 07:55:11 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/10 08:06:28 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_CL_INTERFACE_H
# define RT_CL_INTERFACE_H

# include "rt_obj_types.h"

typedef struct		s_obj
{
	short			type;
	double3			pos;
	double			radius;
}					t_obj;

#endif
