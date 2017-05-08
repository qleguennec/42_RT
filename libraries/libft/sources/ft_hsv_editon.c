/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hsv_editon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 22:11:01 by bsouchet          #+#    #+#             */
/*   Updated: 2017/05/06 22:35:41 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

cl_float3			ft_hsv_to_rgb(t_hsv hsv)
{
	cl_float3	rgb;
	double		p;
	double		q;
	double		t;

	(hsv.h == 360.) ? (hsv.h = 0.) : (hsv.h /= 60.);
	p = hsv.v * (1. - hsv.s);
	q = hsv.v * (1. - (hsv.s * (hsv.h - floor(hsv.h))));
	t = hsv.v * (1. - (hsv.s * (1. - (hsv.h - floor(hsv.h)))));
	rgb = (cl_float3){{ 0.,  0.,  0.}};
	if (hsv.s == 0.)
		rgb = (cl_float3){{ hsv.v,  hsv.v,  hsv.v}};
	else if (0. <= hsv.h && hsv.h < 1.)
		rgb = (cl_float3){{ hsv.v,  t,  p}};
	else if (1. <= hsv.h && hsv.h < 2.)
		rgb = (cl_float3){{ q,  hsv.v,  p}};
	else if (2. <= hsv.h && hsv.h < 3.)
		rgb = (cl_float3){{ p,  hsv.v,  t}};
	else if (3. <= hsv.h && hsv.h < 4.)
		rgb = (cl_float3){{ p,  q,  hsv.v}};
	else if (4. <= hsv.h && hsv.h < 5.)
		rgb = (cl_float3){{ t,  p,  hsv.v}};
	else if (5. <= hsv.h && hsv.h < 6.)
		rgb = (cl_float3){{ hsv.v, p, q}};
	return (rgb);
}

t_hsv 			ft_rgb_to_hsv(t_rgb c)
{
	t_hsv		out;
	double		min;
	double		max;
	double		delta;

	min = (c.r < c.g) ? c.r : c.g;
	min = (min < c.b) ? min : c.b;
	max = (c.r > c.g) ? c.r : c.g;
	max = (max > c.b) ? max : c.b;
	out.v = max;
	delta = max - min;
	if (delta < 0.00001)
	{
		out.s = 0.0f;
		out.h = 0.0f;
		return (out);
	}
	if (max > 0.0f)
		out.s = (delta / max);
	else
	{
		out.s = 0.0f;
		out.h = NAN;
		return out;
	}
	if (c.r >= max)
		out.h = (c.g - c.b) / delta;
	else if (c.g >= max)
		out.h = 2.0f + (c.b - c.r) / delta;
	else
		out.h = 4.0f + (c.r - c.g) / delta;
	out.h *= 60.0f;
	out.h += (out.h < 0.0f) ? 360.0f : 0.0f;
	return (out);
}

t_hsv 			ft_vec_to_hsv(cl_float3 c)
{
	t_hsv		out;
	double		min;
	double		max;
	double		delta;

	min = (c.x < c.y) ? c.x : c.y;
	min = (min < c.z) ? min : c.y;
	max = (c.x > c.y) ? c.x : c.z;
	max = (max > c.z) ? max : c.y;
	out.v = max;
	delta = max - min;
	if (delta < 0.00001)
	{
		out.s = 0.0f;
		out.h = 0.0f;
		return (out);
	}
	if (max > 0.0f)
		out.s = (delta / max);
	else
	{
		out.s = 0.0f;
		out.h = NAN;
		return out;
	}
	if (c.x >= max)
		out.h = (c.y - c.z) / delta;
	else if (c.y >= max)
		out.h = 2.0f + (c.z - c.x) / delta;
	else
		out.h = 4.0f + (c.x - c.y) / delta;
	out.h *= 60.0f;
	out.h += (out.h < 0.0f) ? 360.0f : 0.0f;
	return (out);
}
