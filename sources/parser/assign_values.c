/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_values.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 08:29:18 by bsouchet          #+#    #+#             */
/*   Updated: 2017/01/29 18:31:27 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj		*assign_default_obj_values(t_obj *obj, char t, int type)
{
	obj->id = 1;
	obj->e = 1;
	obj->t = t;
	obj->title = type;
	obj->ot = 1;
	obj->m = -1;
	obj->v = 1;
	obj->i = 10;
	obj->fl = 50;
	obj->n = NULL;
	obj->op = 1.;
	obj->pos = (t_vec3){.0 / .0, .0 / .0, .0 / .0};
	obj->rot = (t_vec3){.0 / .0, .0 / .0, .0 / .0};
	obj->rgb = (t_vec3){.0 / .0, .0 / .0, .0 / .0};
	return (obj);
}

t_obj		*assign_obj_values(t_obj *obj, t_obj *tmp, char t, int type)
{
	if (type < 1)
		return (assign_default_obj_values(obj, t, type));
	obj->e = tmp->e;
	obj->t = t;
	obj->title = 0;
	obj->ot = tmp->ot;
	obj->m = tmp->m;
	obj->v = tmp->v;
	obj->i = tmp->i;
	obj->fl = tmp->fl;
	obj->n = ft_strdup(tmp->n);
	obj->op = tmp->op;
	obj->pos = tmp->pos;
	obj->rot = tmp->rot;
	obj->rgb = tmp->rgb;
	return (obj);
}
