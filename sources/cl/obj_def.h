/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_def.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 10:34:17 by qle-guen          #+#    #+#             */
/*   Updated: 2017/04/18 16:29:24 by erodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_DEF_H
# define OBJ_DEF_H

# include "../../include/obj_types.h"

# define PREC 0.02f
#define PLANE_PREC 0.00001f
# define SAFE 4

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
	// a ajouter avant le lancer de rayon pour chaque objet
	float3			offset;
	///si tu touche a cette structure modifie la jumelle dans cl_buil/interface.h
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
