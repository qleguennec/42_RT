/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 20:06:11 by bsouchet          #+#    #+#             */
/*   Updated: 2017/01/09 16:00:41 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

t_vec3		v3(double const x, double const y, double const z)
{
	t_vec3		vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vec3		*v3_new_vec(double const x, double const y, double const z)
{
	t_vec3		*vec;

	vec = malloc(sizeof(t_vec3));
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return (vec);
}

t_vec3		*v3_copy_vec(t_vec3 const v)
{
	return (v3_new_vec(v.x, v.y, v.z));
}

void		v3_set(t_vec3 *v, double const x, double const y, double const z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

void		v3_free(t_vec3 *v)
{
	if (v)
		free(v);
}

double		v3_access(t_vec3 *v, int i)
{
	if (v)
	{
		if (i == 0)
			return (v->x);
		else if (i == 1)
			return (v->y);
		else if (i == 2)
			return (v->z);
	}
	return (.0);
}
