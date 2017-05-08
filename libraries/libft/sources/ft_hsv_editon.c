/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hsv_editon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 22:11:01 by bsouchet          #+#    #+#             */
/*   Updated: 2017/05/08 20:30:20 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

cl_float3			ft_hsv_to_vec(t_hsv hsv)
{
	double		c;
	double		h_prime;
	double		x;
	double		m;
	cl_float3	vec;

	c = hsv.v * hsv.s;
	h_prime = fmod(hsv.h / 60.0f, 6);
	x = c * (1 - fabs(fmod(h_prime, 2) - 1));
	m = hsv.v - c;
	if (0 <= h_prime && h_prime < 1)
		vec = (cl_float3){{c, x, 0}};
	else if (1 <= h_prime && h_prime < 2)
		vec = (cl_float3){{x, c, 0}};
	else if (2 <= h_prime && h_prime < 3)
		vec = (cl_float3){{0, c, x}};
	else if (3 <= h_prime && h_prime < 4)
		vec = (cl_float3){{0, x, c}};
	else if (4 <= h_prime && h_prime < 5)
		vec = (cl_float3){{x, 0, c}};
	else if (5 <= h_prime && h_prime < 6)
		vec = (cl_float3){{c, 0, x}};
	else
		vec = (cl_float3){{0, 0, 0}};
	vec.x = (vec.x + m) * 255.0f;
	vec.y = (vec.y + m) * 255.0f;
	vec.z = (vec.z + m) * 255.0f;
	return (vec);
}

t_hsv 			ft_rgb_to_hsv(t_rgb c)
{
	t_hsv		out;
	double		min;
	double		max;
	double		delta;

	c.r /= 255.0;
	c.g /= 255.0;
	c.b /= 255.0;
	min = (c.r < c.g) ? c.r : c.g;
	min = (min < c.b) ? min : c.b;
	max = (c.r > c.g) ? c.r : c.g;
	max = (max > c.b) ? max : c.b;
	delta = max - min;
	if(delta > 0.00001)
	{
		if(max == c.r)
			out.h = 60 * (fmod(((c.g - c.b) / delta), 6));
		else if(max == c.g)
			out.h = 60 * (((c.b - c.r) / delta) + 2);
		else if(max == c.b)
			out.h = 60 * (((c.r - c.g) / delta) + 4);
		if(max > 0.00001)
			out.s = delta / max;
		else
			out.s = 0.0f;
		out.v = max;
	}
	else
	{
		out.h = 0.0f;
		out.s = 0.0f;
		out.v = max;
	}
	if(out.h < 0.0f)
		out.h += 360.0f;
	return (out);
}

t_hsv 			ft_vec_to_hsv(cl_float3 c)
{
	t_hsv		out;
	double		min;
	double		max;
	double		delta;

	c.x /= 255.0;
	c.y /= 255.0;
	c.z /= 255.0;
	min = (c.x < c.y) ? c.x : c.y;
	min = (min < c.z) ? min : c.z;
	max = (c.x > c.y) ? c.x : c.y;
	max = (max > c.z) ? max : c.z;
	delta = max - min;
	if(delta > 0.00001)
	{
		if(max == c.x)
			out.h = 60 * (fmod(((c.y - c.z) / delta), 6));
		else if(max == c.y)
			out.h = 60 * (((c.z - c.x) / delta) + 2);
		else if(max == c.z)
			out.h = 60 * (((c.x - c.y) / delta) + 4);
		if(max > 0.00001)
			out.s = delta / max;
		else
			out.s = 0.0f;
		out.v = max;
	}
	else
	{
		out.h = 0.0f;
		out.s = 0.0f;
		out.v = max;
	}
	if(out.h < 0.0f)
		out.h += 360.0f;
	return (out);
}
