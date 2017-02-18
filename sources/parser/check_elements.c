/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 01:19:11 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/16 21:42:56 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Fonctions to check all elements (cameras, lights & objects).
*/

int			check_rgb_color(cl_float3 clr)
{
	if (clr.x < .0 || clr.x > 255.0)
		return (0);
	if (clr.y < .0 || clr.y > 255.0)
		return (0);
	if (clr.z < .0 || clr.z > 255.0)
		return (0);
	return (1);
}

int			check_scene(t_rt *rt)
{
	if (rt->scn->ambient < 0. || rt->scn->ambient > 1.)
		return (error(rt, 11));
	if (rt->scn->aa != 0 && rt->scn->aa != 2 && rt->scn->aa != 4
		&& rt->scn->aa != 8 && rt->scn->aa != 16)
		return (error(rt, 12));
	if (rt->scn->m_ref < 0 || rt->scn->m_ref > 10)
		return (error(rt, 13));
	rt->prs->i += 8;
	return (1);
}

int			check_camera(t_rt *rt, t_obj *tmp, short i)
{
	tmp->title = 0;
	if (!tmp->n)
		tmp->n = (cl_char *)ft_strjoin("Camera ", ft_itoa(i), 'R');
	if (rt->prs->t[1] != 0)
		return (error(rt, 33));
	if (rt->prs->t[2] == 0)
		return (error(rt, 24));
	if (rt->prs->t[3] == 0)
		return (error(rt, 25));
	if (rt->prs->t[4] != 0)
		return (error(rt, 34));
	if (rt->prs->t[5] != 0 && (tmp->focal < 18 || tmp->focal > 200))
		return (error(rt, 16));
	rt->scn->o = lst_new_camera(rt, rt->scn->o, 0);
	reset_tags(rt->prs);
	rt->prs->i += 9;
	return (1);
}

int			check_light(t_rt *rt, t_obj *tmp, short i)
{
	tmp->title = 0;
	if (rt->prs->t[8] == 0)
		return (error(rt, 41));
	i = ++rt->scn->lt[tmp->forme];
	if (!tmp->n)
		tmp->n = (cl_char *)ft_strjoin(light_type(tmp->forme), ft_itoa(i), 'R');
	if (rt->prs->t[0] == 0 && rt->prs->t[1] == 0)
		rt->prs->obj_tmp->clr = (cl_float3){{255., 219., 74., 255.}};
	if (rt->prs->t[0] != 0 && !check_rgb_color(tmp->clr))
		return (error(rt, 36));
	if (rt->prs->t[2] == 0)
		return (error(rt, 26));
	if (rt->prs->t[6] != 0 && (tmp->intensity < 0. || tmp->intensity > 50.))
		return (error(rt, 35));
	rt->scn->o = lst_new_light(rt, rt->scn->o, 0);
	reset_tags(rt->prs);
	rt->prs->i += 8;
	return (1);
}

int			check_object(t_rt *rt, t_obj *t, short i)
{
	t->title = 0;
	if (rt->prs->t[8] == 0)
		return (error(rt, 28));
	i = ++rt->scn->ot[t->forme];
	if (!t->n)
		t->n = (cl_char *)ft_strjoin(shape_object(t->forme), ft_itoa(i), 'R');
	if (rt->prs->t[1] != 0 && !check_rgb_color(t->clr))
		return (error(rt, 37));
	if (rt->prs->t[2] == 0)
		return (error(rt, 27));
	if (rt->prs->t[7] != 0 && (t->opacity < .0 || t->opacity > 1.0))
		return (error(rt, 10));
	if (rt->prs->t[9] != 0 && (t->radius < .0 || t->radius > 200.0))
		return (error(rt, 38));
	if (rt->prs->t[10] != 0 && (t->width < .0 || t->width > 200.0))
		return (error(rt, 39));
	if (rt->prs->t[11] != 0 && (t->height < .0 || t->height > 200.0))
		return (error(rt, 40));
	rt->scn->o = lst_new_object(rt, rt->scn->o, 0, 0);
	reset_tags(rt->prs);
	rt->prs->i += 9;
	return (1);
}
