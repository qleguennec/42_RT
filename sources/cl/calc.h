/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 14:37:37 by lgatibel          #+#    #+#             */
/*   Updated: 2017/02/14 17:22:33 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALC_H
#define CALC_H
float			calc_delta(float a, float b, float c);
float			norm(global t_obj *obj, float delta, float3 ray_pos, float3 ray_dir);
float3			touch_object(global t_obj *tab_objs, short nobjs, float3 ray_pos, float3 ray_dir, short *id);
float			ray_plane_norm(global t_obj *obj, float3 ray_pos, float3 ray_dir);
float			ray_cone_norm(global t_obj *obj, float3 ray_pos, float3 ray_dir);
float			ray_cylinder_norm(global t_obj *obj, float3 ray_pos, float3 ray_dir);
float			ray_sphere_norm(global t_obj *obj, float3 ray_pos, float3 ray_dir);
void			calc(global unsigned int *pixel, global t_obj *objs, global t_lgt *lgts, short nobjs, short nlgts, float3 ray_pos, float3 ray_dir, global t_cam *cam);
float			float3_to_float(float3 v);
#endif
