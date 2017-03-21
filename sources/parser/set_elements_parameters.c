/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elements_parameters.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 15:13:44 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/23 18:29:19 by bsouchet         ###   ########.fr       */
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
	obj->clr = (cl_float3){{.5, .5, .5, .5}};
	obj->opacity = 1.;
	obj->focal = 55;
	obj->radius = 25.0;
	obj->lenght = 50.0;
	obj->width = 50.0;
	obj->height = 50.0;
	obj->material = 0;
	obj->visibility = 1;
	obj->flare_v = 1;
	obj->intensity = 10.;
	obj->shiness = .0;
	obj->mshiness = .0;
	obj->reflex = .0;
	obj->refract = .0;
	obj->r_ol = (SDL_Rect){0, 0, 0, 0};
	return (obj);
}

t_obj		*set_element_parameters(t_obj *obj, t_obj *tmp, char t, int title)
{
	if (title != 0)
		return (set_default_parameters(obj, t, title));
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
	obj->lenght = tmp->lenght;
	obj->width = tmp->width;
	obj->height = tmp->height;
	obj->visibility = tmp->visibility;
	obj->flare_v = tmp->flare_v;
	obj->intensity = tmp->intensity;
	obj->shiness = tmp->shiness;
	obj->mshiness = tmp->shiness;
	obj->material = tmp->material;
	obj->reflex = tmp->reflex;
	obj->refract = tmp->refract;
	return (obj);
}
