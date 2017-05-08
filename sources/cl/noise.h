/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erodrigu <erodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 16:38:12 by erodrigu          #+#    #+#             */
/*   Updated: 2017/05/08 16:40:33 by erodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOISE_H
#define NOISE_H

double rand_noise(int t);
double noise_3d(int x, int y, int z);
double smooth_noise_3d(float3 pos);
double cosine_interpolate(double a, double b, double t);
#endif
