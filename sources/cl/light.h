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
# define SPECUL 0.75f
# define POW_SPECUL 250

unsigned	get_lighting(t_data * data);
float3		is_light(t_data * data, float3 lightdir, global t_lgt *lgt);
float3		calcul_clr(float3 ray, float3 normale, float3 light);
unsigned	calcul_rendu_light(t_data *data);
float3		calcul_normale(t_data *data);
void		clearness_calcul(t_data *data);
float3		is_shining(float3 normale, float3 lightdir, float3 lightcolor);
float3		check_all_light(t_data *data);
void		calcul_light(float3 *light_clr, global t_obj *obj);
void		calcul_reflex_ray(t_data * data);
float		my_dot(float3 v1, float3 v2);
void		clearness_calcul(t_data *data);
void		clearness_color(t_data *data);
void		get_color(t_data *data);

float3		calcul_refract_ray(t_data *data, float refract1, float refract2);
#endif
