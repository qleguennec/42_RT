/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erodrigu <erodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 14:37:00 by erodrigu          #+#    #+#             */
/*   Updated: 2017/04/18 14:53:41 by erodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
#define LIGHT_H
#include "calc.h"
#include "obj_def.h"

unsigned	get_lighting(t_data * data);
float3		is_light(t_data * data, float3 lightdir, global t_lgt *lgt,
	float3 normale);
float3		calcul_clr(float3 ray, float3 normale, float3 light,
	global t_obj *obj);
unsigned	calcul_rendu_light(t_data *data);
float3		calcul_normale(t_data *data);
void		clearness_calcul(t_data *data);
float3		is_shining(float3 normale, float3 lightdir, float int_specul,
	float pow_specul, float3 lightcolor);
float3		check_all_light(t_data *data);
void		calcul_light(float3 *light_clr, global t_obj *obj);
void		calcul_reflex_ray(t_data * data, float3 *ray_pos, float3 *ray_dir);
float		my_dot(float3 v1, float3 v2);
void		clearness_calcul(t_data *data);
void		clearness_color(t_data *data);
void		get_color(t_data *data);
float3		calcul_refract_ray(t_data *data, float refract1, float refract2);
void		calcul_reflex_color(t_data *data);
void		init_laputain_desamere(t_data *data);

#endif
