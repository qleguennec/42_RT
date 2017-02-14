/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shiness.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erodrigu <erodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 12:44:21 by erodrigu          #+#    #+#             */
/*   Updated: 2017/02/13 12:44:30 by erodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

include "light.h"


float3	is_shining(float3 normale, float3 lightdir, float int_specul,
	float pow_specul, float3 dif_color, float3 lightcolor)
{
	float3	r;
	float3	v;

	v = lightdir - 2.0f * normale * my_dot(normale, lightdir);
	r = lightdir + v;
	return (lightcolor * dif_color * int_specul * pow(my_dot(r, v), pow_specul));
}
