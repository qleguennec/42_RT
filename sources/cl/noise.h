/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erodrigu <erodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 16:38:12 by erodrigu          #+#    #+#             */
/*   Updated: 2017/05/09 18:07:29 by erodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOISE_H
#define NOISE_H
#define OCTAVE 10
#define FREQUENCY 0.0625
#define PERSIS 0.40

typedef struct			s_shader
{
	float3	col1;
	float3	col2;
	float3	col3;
}						t_shader;

float3	wood_shaders(float3 pos);
float3	lerp_wood(float v, t_shader colors);

float3	get_shaders(float3 pos, int shader);
void	get_bumpmapping(t_data *data);

double	rand_noise(int t);
double	noise_3d(int x, int y, int z);
double	smooth_noise_3d(float3 pos);
double	cosine_interpolate(double a, double b, double t);
double	perlin(int octaves, float frequency, float persistence, float3 pos);
#endif
