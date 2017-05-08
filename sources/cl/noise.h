/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erodrigu <erodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 16:38:12 by erodrigu          #+#    #+#             */
/*   Updated: 2017/05/08 18:38:20 by erodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOISE_H
#define NOISE_H
#define OCTAVE 100
#define FREQUENCY 0.25
#define PERSIS 0.2

double rand_noise(int t);
double noise_3d(int x, int y, int z);
double smooth_noise_3d(float3 pos);
double cosine_interpolate(double a, double b, double t);
double perlin(int octaves, float frequency, float persistence, float3 pos);
#endif
