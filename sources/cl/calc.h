/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <lgatibel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 14:37:37 by lgatibel          #+#    #+#             */
/*   Updated: 2017/03/21 20:06:08 by erodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALC_H
#define CALC_H

typedef struct			s_data
{
	global t_obj		*objs;
	global t_obj		*obj;
	global t_lgt		*lights;
	global unsigned int	*pixel;
	short				n_objs;
	short				n_lgts;
	short				id;
	short				safe;
	float				ambiant;
	float				light_pow;
	float3				ray_pos;
	float3				ray_dir;
	float3				intersect;
	float3				rd_light;
	float3				offset;
	float3				rad;
	short				nl;
}						t_data;

float			calc_delta(float a, float b, float c);

void			calc_intersect(float *delta, float3 *ray_pos, float3 *ray_dir,
 float3 *intersect);

void			touch_object(t_data *data);

short			plane_intersection(t_data *data);

short			cone_intersection(t_data *data);

short			cylinder_intersection(t_data *data);

short			sphere_intersection(t_data *data);

void			calc_picture(int debug, global unsigned int *pixel, global t_obj *objs,
 global t_lgt *lgts, short nobjs, short nlgts, float3 ray_pos, float3 ray_dir,
  global t_cam *cam, short x, short y);

float			float3_to_float(float3 v);
// rotation function
float3			rotate_ray(float3 *ray, t_data *data);
void			rotate_pos_x(t_data *data);
void			rotate_pos_y(t_data *data);
void			rotate_pos_z(t_data *data);

float3			rotate_x(float3 *ray, float rad);
float3			rotate_y(float3 *ray, float rad);
float3			rotate_z(float3 *ray, float rad);
#endif
