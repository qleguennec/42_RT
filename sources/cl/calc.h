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

void			calc_intesect(float *delta, float3 *ray_pos, float3 *ray_dir, float3 *intersect);

float3			touch_object(t_data *data);

short			plane_intersection(t_data *data, global t_obj *obj);

short			cone_intersection(t_data *data, global t_obj *obj);

short			cylinder_intersection(t_data *data, global t_obj *obj);

short			sphere_intersection(t_data *data, global t_obj *obj);

void			calc(int debug ,global unsigned int *pixel, global t_obj *objs, global t_lgt *lgts, short nobjs, short nlgts, float3 ray_pos, float3 ray_dir, global t_cam *cam, short x, short y);

float			float3_to_float(float3 v);
// rotation function
float3			rotate_x(float3 * ray, global t_obj *obj, float3 *offset);
float3			rotate_y(float3 * ray, global t_obj *obj, float3 *offset);
float3			rotate_z(float3 * ray, global t_obj *obj, float3 *offset);
#endif
