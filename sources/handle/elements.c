/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:56:13 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/13 10:19:43 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		add_new_camera(t_rt *rt, t_obj *tmp)
{
	draw_button(rt, 2, -1);
	tmp = set_default_parameters(rt->prs->obj_tmp, 'C', 0);
	tmp->n = (cl_char *)ft_strjoin("Camera ", ft_itoa(rt->scn->n_cams), 'R');
	tmp->focal = rt->scn->c_cam->focal;
	tmp->pos.x = rt->scn->c_cam->pos.x;
	tmp->pos.y = rt->scn->c_cam->pos.y;
	tmp->pos.z = rt->scn->c_cam->pos.z;
	tmp->rot.x = rt->scn->c_cam->rot.x;
	tmp->rot.y = rt->scn->c_cam->rot.y;
	tmp->rot.z = rt->scn->c_cam->rot.z;
	rt->scn->o = lst_new_camera(rt, rt->scn->o, 0);
	rt->ui->area[4].h += 29;
	(rt->scn->n_elms >= 15) ? (rt->ui->nav_state = 1) : 1;
	(rt->r_view.x != 18) ? draw_outliner(rt, -1, 0) : 1;
}

void		add_new_light(t_rt *rt, t_obj *tmp, short type)
{
	draw_button(rt, 2, -1);
	tmp = set_default_parameters(rt->prs->obj_tmp, 'L', 0);
	if (type == T_DIFFUSE && ++rt->scn->lt[0])
		tmp->n = (cl_char *)ft_strjoin("Point Light ",
		ft_itoa(rt->scn->lt[0]), 'R');
	else if (type == T_DIRECTIONAL && ++rt->scn->lt[1])
		tmp->n = (cl_char *)ft_strjoin("Directional Light ",
		ft_itoa(rt->scn->lt[1]), 'R');
	else if (++rt->scn->lt[2])
		tmp->n = (cl_char *)ft_strjoin("Spot Light ",
		ft_itoa(rt->scn->lt[2]), 'R');
	tmp->forme = type;
	tmp->clr = (cl_float3){{255., 219., 74., 255.}};
	rt->scn->o = lst_new_light(rt, rt->scn->o, 0);
	rt->ui->area[4].h += 29;
	(rt->scn->n_elms >= 15) ? (rt->ui->nav_state = 1) : 1;
	(rt->r_view.x != 18) ? draw_outliner(rt, -1, 0) : 1;
}

void		add_new_object(t_rt *rt, t_obj *tmp, short type)
{
	draw_button(rt, 2, -1);
	++rt->scn->ot[type];
	tmp = set_default_parameters(rt->prs->obj_tmp, 'O', 0);
	tmp->n = (cl_char *)ft_strjoin(shape_object(type),
	ft_itoa(rt->scn->ot[type]), 'R');
	tmp->forme = type;
	rt->scn->o = lst_new_object(rt, rt->scn->o, 0, 0);
	rt->ui->area[4].h += 29;
	(rt->scn->n_elms >= 15) ? (rt->ui->nav_state = 1) : 1;
	(rt->r_view.x != 18) ? draw_outliner(rt, -1, 0) : 1;
}

void		add_new_shader(t_obj *obj, short type)
{
	obj->material = type;
	if (type < 2)
		obj->shiness = (1) ? 0. : 0.;
	else
		obj->shiness = (1) ? 0. : 0.;
	if (type < 2)
		obj->mshiness = (1) ? 0. : 0.;
	else
		obj->mshiness = (1) ? 0. : 0.;
	if (type < 2)
		obj->specolor = (1) ? 0. : 0.;
	else
		obj->specolor = (1) ? 0. : 0.;
	if (type < 2)
		obj->reflex = (1) ? 0. : 0.;
	else
		obj->reflex = (1) ? 0. : 0.;
	if (type < 2)
		obj->refract = (1) ? 0. : 0.;
	else
		obj->refract = (1) ? 0. : 0.;
}