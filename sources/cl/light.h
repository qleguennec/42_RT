/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erodrigu <erodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 14:37:00 by erodrigu          #+#    #+#             */
/*   Updated: 2017/03/15 16:09:21 by erodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "calc.h"
#include "obj_def.h"

unsigned	get_lighting(t_data * data);

float3		is_light(t_data * data, float3 lightpos, float3 lightdir, global t_obj *objs,
	global t_lgt *light, short n_objs, short n_lights, float3 normale,
	short obj_ind);

float3		calcul_clr(float3 ray, float3 normale, float3 light,
	global t_obj *obj);

unsigned	calcul_rendu_light(float3 light, short n_lights, float ambiant);

float3		calcul_normale(global t_obj *obj, float3 *point);

float3		is_shining(float3 normale, float3 lightdir, float int_specul,
	float pow_specul, float3 dif_color, float3 lightcolor);

float3		check_all_light(t_data * data, global t_lgt *lights, short n_lights,
	global t_obj *objs, short n_objs, short obj_ind, float ambiant,
	float3 *ray_dir, float3 *ray_pos);

void		calcul_light(float3 *light_clr, global t_obj *obj);

void		reflex_calcul(t_data * data, global t_obj *objs, global t_lgt *lights,
	short n_objs, short n_lights, float3 *ray_pos, float3 *ray_dir,
	float ambiant, short obj_ind, float *light_power, float3 *rd_light,
	short *safe);

void		calcul_reflex_ray(t_data * data, float3 *ray_pos, float3 *ray_dir, global t_obj *objs,
	short obj_ind);

float		my_dot(float3 v1, float3 v2);

void		clearness_calcul(t_data * data, global t_obj *objs, global t_lgt *lights,
	short n_objs, short n_lights, float3 *new_pos, float3 *ray_dir, short *safe,
	short obj_ind, float *light_power, float3 *rd_light, float ambiant);

void		clearness_color(t_data * data, global t_obj *objs, global t_lgt *lights,
	short n_objs, short n_lights, float3 *ray_pos, float3 *ray_dir, short *safe,
	short obj_ind, float *light_power, float3 *rd_light, float ambiant);

void		get_color(t_data * data, global t_obj *objs, global t_lgt *lights,
	short n_objs, short n_lights, float3 *ray_pos, float3 *ray_dir,
	short obj_ind, float *light_power, float3 *rd_light, short *safe,
	float ambiant);

float3		calcul_refract_ray(t_data * data, float3 *ray_dir, float3 *ray_pos, global t_obj *obj,
	float refract1, float refract2);
