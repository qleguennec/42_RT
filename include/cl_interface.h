/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cl_interface.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 07:55:11 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/10 08:23:04 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_CL_INTERFACE_H
# define RT_CL_INTERFACE_H

typedef struct		s_obj
{
	short			type;
	short			visibility;
	float3			pos;
	float3			rot;
	float3			clr;
	float			opacity;
	float			width;
	float			height;
	float			radius;
	float			intensity;
	float			shineness;
	float			mshineness;
	float			specolor;
	float			reflex;
	float			refract;
}					t_obj;

#endif
