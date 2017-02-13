/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elements_parameters.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 15:13:44 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/11 22:18:14 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj		*set_default_parameters(t_obj *obj, char type, int title)
{
	obj->id = 1;
	obj->n = NULL;
	obj->title = title;
	obj->active = 0;
	obj->type = type;
	obj->forme = -1;
	obj->pos = (cl_float3){{0., 0., 0., 0.}};
	obj->rot = (cl_float3){{0., 0., 0., 0.}};
	obj->clr = (cl_float3){{128., 128., 128., 128.}};
	obj->opacity = 1.;
	obj->focal = 50;
	obj->radius = 0.5;
	obj->width = 1;
	obj->height = 1;
	obj->visibility = 1;
	obj->intensity = 10.;
	obj->shiness = .0;
	obj->mshiness = .0;
	obj->reflex = .0;
	obj->refract = .0;
	obj->r_ol = (SDL_Rect){0, 0, 0, 0};
	return (obj);
}

t_obj		*set_element_parameters(t_obj *obj, t_obj *tmp, char type, int title)
{
	if (title != 0)
		return (set_default_parameters(obj, type, title));
	obj->n = (tmp->n) ? tmp->n : NULL;
	obj->type = tmp->type;
	obj->title = tmp->title;
	obj->forme = tmp->forme;
	obj->pos = tmp->pos;
	obj->rot = tmp->rot;
	obj->clr = tmp->clr;
	obj->opacity = tmp->opacity;
	obj->focal = tmp->focal;
	obj->radius = tmp->radius;
	obj->width = tmp->width;
	obj->height = tmp->height;
	obj->visibility = tmp->visibility;
	obj->intensity = tmp->intensity;
	obj->shiness = tmp->shiness;
	obj->mshiness = tmp->shiness;
	obj->reflex = tmp->reflex;
	obj->refract = tmp->refract;
	return (obj);
}
