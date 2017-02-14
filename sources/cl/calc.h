/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 14:37:37 by lgatibel          #+#    #+#             */
/*   Updated: 2017/02/14 15:10:47 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALC_H
#define CALC_H

///////////////////////////////////////////////////////// A SUPPRIMER
#define T_PLANE 0
#define T_CONE 1
#define T_SPHERE 2
#define T_CYLINDER 3
/////////////////////////////////////////////////////// A SUPRIMER
float			delta(float a, float b, float c);
float			norm(t_obj obj, float delta, float3 ray_pos, float3 ray_dir);
float			ray_plane_norm(t_obj *obj, float3 ray_pos, float3 ray_dir);
float			ray_cone_norm(t_obj *obj, float3 ray_pos, float3 ray_dir);
float			ray_cylinder_norm(t_obj *obj, float3 ray_pos, float3 ray_dir);
float			ray_sphere_norm(t_obj *obj, float3 ray_pos, float3 ray_dir);
#endif
