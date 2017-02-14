/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 14:37:37 by lgatibel          #+#    #+#             */
/*   Updated: 2017/02/14 15:36:55 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALC_H
#define CALC_H

float			delta(float a, float b, float c);
float			norm(t_obj obj, float delta, float3 ray_pos, float3 ray_dir);
short	touch_object(t_obj tab_objs, short nobjs, float3 ray_pos, float3 ray_dir, float *t);
float			ray_plane_norm(t_obj *obj, float3 ray_pos, float3 ray_dir);
float			ray_cone_norm(t_obj *obj, float3 ray_pos, float3 ray_dir);
float			ray_cylinder_norm(t_obj *obj, float3 ray_pos, float3 ray_dir);
float			ray_sphere_norm(t_obj *obj, float3 ray_pos, float3 ray_dir);
void			calc(int *pixel, t_obj objs, t_obj *lgts, short nobjs, short nlgts, float3 ray_pos, float3 ray_dir);
#endif
