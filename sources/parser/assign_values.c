/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_values.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 08:29:18 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/09 21:23:06 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj		*assign_default_obj_values(t_obj *obj, char t, int type)
{
	obj->id = 1;
	obj->type = t;
	obj->title = type;
	obj->visibility = 1;
	obj->intensity = 10;
	obj->focal = 50;
	obj->n = NULL;
	obj->opacity = 1.;
	obj->pos = (cl_float3){{0. / 0., 0. / 0., 0. / 0., 0. / 0.}};
	obj->rot = (cl_float3){{0. / 0., 0. / 0., 0. / 0., 0. / 0.}};
	obj->clr = (cl_float3){{0. / 0., 0. / 0., 0. / 0., 0. / 0.}};
	return (obj);
}

t_obj		*assign_obj_values(t_obj *obj, t_obj *tmp, char t, int type)
{
	if (type < 1)
		return (assign_default_obj_values(obj, t, type));
	obj->type = t;
	obj->title = 0;
	obj->visibility = tmp->visibility;
	obj->intensity = tmp->intensity;
	obj->focal = tmp->focal;
	obj->n = (cl_char *)ft_strdup((char *)tmp->n);
	obj->opacity = tmp->opacity;
	obj->pos = tmp->pos;
	obj->rot = tmp->rot;
	obj->clr = tmp->clr;
	return (obj);
}
