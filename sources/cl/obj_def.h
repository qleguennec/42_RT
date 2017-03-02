/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_def.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 10:34:17 by qle-guen          #+#    #+#             */
/*   Updated: 2017/03/02 12:33:27 by erodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_DEF_H
# define OBJ_DEF_H

# include "../../include/obj_types.h"

# define PREC 0.0000001f
# define SAFE 10

typedef struct		s_obj
{
	short			type;
	float3			pos;
	float3			rot;
	float3			clr;
	float			opacity;
	float			width;
	float			height;
	float			radius;
	float			specolor;
	float			reflex;
	float			refract;
	float			shiness;
	float			mshiness;
}					t_obj;

typedef struct		s_lgt
{
	float3			pos;
	float3			rot;
	float3			clr;
	float			intensity;
}					t_lgt;

typedef struct		s_cam
{
	float3			pos;
	float3			rot;
	short			focal;
}					t_cam;

#endif
