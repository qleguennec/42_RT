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
# define CALC_H

typedef struct			s_data
{
	global t_obj		*objs;
	global t_obj		*obj;
	global t_lgt		*lights;
	global unsigned int	*pixel;
	short				n_objs;
	short				n_lgts;
	float3				ray_pos;
	float3				ray_dir;
	float3				intersect;
	float3				save_pos;
	float3				save_dir;
	float3				save_inter;
	float3				save_clr;
	short				save_id;
	short				through;
	short				test;
	float				ambiant;
	float				light_pow;
	float				light_obj_pow;
	float3				rd_light;
	short				id;
	short				reflex;
	short				type;
	float3				pos;
	short				is_light;
	float3				inter;
	float3				clr;
	short				nl;
	float				t;
	float				t0;
	float				t1;
	float3				offset;
}						t_data;

float			calc_delta(float3 *disc, t_data *data);

void			calc_intersect(t_data *data);

void			touch_object(t_data *data);
void			touch_object2(t_data *data);

short			plane_intersection(t_data *data, short *index);

short			cone_intersection(t_data *data, short *index);
short			cone_caps(t_data *data, float3 *rot, short *index, float m);

short			cylinder_caps(t_data *data, float3 *rot, short *index, float m);



short			cylinder_intersection(t_data *data, short *index);

short			sphere_intersection(t_data *data, short *index);

short			disk_intersection(t_data *data, short *index);

void			calc_picture(int debug, global unsigned int *pixel, global t_obj *objs,
 global t_lgt *lgts, short nobjs, short nlgts, float3 ray_pos, float3 ray_dir,
  global t_cam *cam, short x, short y);

float3			rotate_ray(t_data *data, short *index);
float3			rotate_cam(float3 rot);

float3		calcul_normale(t_data *data);

void		init(t_data *data, global t_obj *objs,
global t_lgt *lgts, short n_objs, short n_lgts, float3 ray_pos,
float3 ray_dir, float ambiant, global unsigned int *pixel);

void    save(t_data *data);
void    load(t_data *data);
#endif
