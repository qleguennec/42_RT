/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <lgatibel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 14:37:37 by lgatibel          #+#    #+#             */
/*   Updated: 2017/03/03 15:20:02 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALC_H
#define CALC_H
float			calc_delta(float a, float b, float c);
void			norm(float delta, float3 ray_pos, float3 ray_dir, float3 * intersect);
float3			touch_object(global t_obj *tab_objs, short nobjs, float3 ray_pos, float3 ray_dir, short *id);
short			ray_plane_intersection(global t_obj *obj, float3 ray_pos, float3 ray_dir, float3 *intersect);
short			ray_cone_intersection(global t_obj *obj, float3 ray_pos, float3 ray_dir, float3 *intersect);
short			ray_cylinder_intersection(global t_obj *obj, float3 ray_pos, float3 ray_dir, float3 *intersect);
short			ray_sphere_intersection(global t_obj *obj, float3 ray_pos, float3 ray_dir, float3 *intersect);
void			calc(int debug ,global unsigned int *pixel, global t_obj *objs, global t_lgt *lgts, short nobjs, short nlgts, float3 ray_pos, float3 ray_dir, global t_cam *cam, short x, short y);
float			float3_to_float(float3 v);
#endif
