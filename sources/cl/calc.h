/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <lgatibel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 14:37:37 by lgatibel          #+#    #+#             */
/*   Updated: 2017/03/09 16:15:32 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALC_H
#define CALC_H
typedef struct			s_data
{
	global t_obj		*objs;
	global t_lgt		*lgts;
	global unsigned int	*pixel;
	short				n_objs;
	short				n_lgts;
	float3				ray_pos;
	float3				ray_dir;
	float				ambiant;
	short				id;
	float3				intersect;
}						t_data;

float			calc_delta(float a, float b, float c);

void			norm(float delta, t_data *data);

float3			touch_object(t_data *data);

short			ray_plane_intersection(t_data *data, global t_obj *obj);

short			ray_cone_intersection(t_data *data, global t_obj *obj);

short			ray_cylinder_intersection(t_data *data, global t_obj *obj);

short			ray_sphere_intersection(t_data *data, global t_obj *obj);

void			calc(int debug ,global unsigned int *pixel, global t_obj *objs, global t_lgt *lgts, short nobjs, short nlgts, float3 ray_pos, float3 ray_dir, global t_cam *cam, short x, short y);

float			float3_to_float(float3 v);
#endif
