/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <lgatibel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 14:37:37 by lgatibel          #+#    #+#             */
/*   Updated: 2017/04/07 11:46:31 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALC_H
#define CALC_H
// structure for image computing
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
	short				option;
	short				nl;

	short				test;
	short				set;
	float3				rot;
	float3				pos;
	float				radius;
	float3				off_set;
	float				t;
//	float				delta;

	float				ambiant;
	float				light_pow;
	float3				ray_pos;
	float3				grid_ray_dir;
	float3				ray_dir;
	float3				intersect;
	float3				grid_intersect;
	float3				rd_light;
	float3				offset;
	float3				rdir;
	// float3				rad;
}						t_data;
/////////////////////

// object intersection
float			calc_delta(float a, float b, float c);

void			calc_intersect(float *delta, t_data *data);

void			touch_object(t_data *data);

short			plane_intersection(t_data *data, short *index);

short			cone_intersection(t_data *data, short *index);

short			cylinder_intersection(t_data *data, short *index);

short			sphere_intersection(t_data *data, short *index);

short			disk_intersection(t_data *data, short *index);
/////////////////////

// entry function
void			calc_picture(int debug, global unsigned int *pixel, global t_obj *objs,
 global t_lgt *lgts, short nobjs, short nlgts, float3 ray_pos, float3 ray_dir,
  global t_cam *cam, short x, short y);
/////////////////////

// tools
float			float3_to_float(float3 v);
/////////////////////

// rotate function
float3			rotate_ray(float3 *ray, t_data *data, short *index);
/////////////////////
#endif
