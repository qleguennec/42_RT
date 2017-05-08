/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elements_parameters.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 15:13:44 by bsouchet          #+#    #+#             */
/*   Updated: 2017/03/02 20:16:44 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj		*set_default_parameters(t_obj *obj, char type, int title)
{
	obj->n = NULL;
	obj->title = title;
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
	obj->shiness = .0; // Will Be Useless One Day
	obj->mshiness = .0; // Will Be Useless One Day
	obj->reflex = .0;
	obj->refract = .0; // Will Be Useless One Day
	obj->refrac_i = 1.0;
	obj->refrac_y = 0.1;
	obj->specular = .0;
	obj->texture = NULL;
	obj->p_texture = -1;
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
	obj->shiness = tmp->shiness; // Will Be Useless One Day
	obj->mshiness = tmp->shiness; // Will Be Useless One Day
	obj->material = tmp->material;
	obj->reflex = tmp->reflex;
	obj->refract = tmp->refract; // Will Be Useless One Day
	obj->refrac_i = tmp->refrac_i;
	obj->refrac_y = tmp->refrac_y;
	obj->specular = tmp->specular;
	obj->texture = tmp->texture;
	obj->p_texture = tmp->p_texture;
	return (obj);
}
