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

float3	is_shining(float3 normale, float3 lightdir, float int_specul,
	float pow_specul, float3 lightcolor)
{
	float3	r;
	float3	v;

	r = fast_normalize(lightdir - 2.0f * normale * dot(normale, lightdir));
	v = fast_normalize(2.0f * normale * (dot(-normale, lightdir)));
	return (lightcolor * int_specul * pow(dot(r, v), pow_specul));
}
