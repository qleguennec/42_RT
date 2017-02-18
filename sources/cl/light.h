/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erodrigu <erodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 14:37:00 by erodrigu          #+#    #+#             */
/*   Updated: 2017/02/18 18:16:06 by erodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned get_lighting(global t_obj *objs, global t_lgt *lights,
	short n_objs, short n_lights,/* float ambiant,*/ float3 ray_pos, float3 ray_dir,
	short obj_ind);
float3	is_light(float3 lightpos, float3 lightdir, global t_obj *objs, global t_lgt *light,
	short n_objs, short n_lights, float3 normale, short obj_ind);
float3	calcul_light(float3 ray, float3 normale, global t_lgt *light,
	global t_obj *obj);
unsigned	calcul_rendu_light(float3 light, short n_lights);
float	my_dot(float3 v1, float3 v2);
float3	calcul_normale(global t_obj *obj, float3 point);
unsigned	twocolor_lerp(float3 a, unsigned b, short pc);
float3	is_shining(float3 normale, float3 lightdir, float int_specul,
	float pow_specul, float3 dif_color, float3 lightcolor);
