/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 02:06:16 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/02 18:19:56 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Fonctions to get & assign values to elements of the scene
*/

int			set_scene(t_rt *rt, int b_end, int e)
{
	while (e != -1 && rt->prs->i < b_end)
	{
		if ((e = check_balises(rt, BO_N, BC_N)) > 1)
			rt->scn->name = get_s(rt->prs, e, 7);
		else if (e > -1 && (e = check_balises(rt, BO_A, BC_A)) > 1)
			(get_d(rt, e, BO_A, BC_A)) ?
			d(&rt->scn->ambient, rt->prs->t_d) : (e = -1);
		else if (e > -1 && (e = check_balises(rt, BO_AA, BC_AA)) > 1)
			(get_i(rt, e, BO_AA, BC_AA)) ?
			i(&rt->scn->aa, rt->prs->t_i) : (e = -1);
		else if (e > -1 && (e = check_balises(rt, BO_MR, BC_MR)) > 1)
			(get_i(rt, e, BO_MR, BC_MR)) ?
			i(&rt->scn->m_ref, rt->prs->t_i) : (e = -1);
		else if (e > -1 && (rt->prs->b_o = BO_S) &&
		(rt->prs->b_c = BC_S))
			return (error(rt, 10, 2));
	}
	return ((e != -1) ? check_scene(rt) : e);
}

static int	add_element_parameters(t_rt *rt, int e, char type)
{
	if (e > -1 && type == 'C' && (e = check_balises(rt, BO_FL, BC_FL)) > 1)
		(get_i(rt, e, BO_FL, BC_FL)) ?
		(rt->prs->obj_tmp->fl = rt->prs->t_i) : i(&e, -1);
	else if (e > -1 && type == 'L' && (e = check_balises(rt, BO_V, BC_V)) > 1)
		(get_b(rt, e, BO_V, BC_V)) ?
		(rt->prs->obj_tmp->v = rt->prs->t_i) : i(&e, -1);
	else if (e > -1 && type == 'L' && (e = check_balises(rt, BO_I, BC_I)) > 1)
		(get_d(rt, e, BO_I, BC_I)) ?
		(rt->prs->obj_tmp->i = rt->prs->t_d) : i(&e, -1);
	else if (e > -1 && type == 'O' && (e = check_balises(rt, BO_T, BC_T)) > 1)
		(get_t(rt, e, BO_T, BC_T)) ?
		(rt->prs->obj_tmp->ot = rt->prs->t_i) : i(&e, -1);
	else if (e > -1 && type == 'O' && (e = check_balises(rt, BO_OP, BC_OP)) > 1)
		(get_d(rt, e, BO_OP, BC_OP)) ?
		(rt->prs->obj_tmp->op = rt->prs->t_d) : i(&e, -1);
	else if (e > -1 && type == 'O' && (e = check_balises(rt, BO_M, BC_M)) > 1)
		(get_m(rt, e, BO_M, BC_M)) ?
		(rt->prs->obj_tmp->m = rt->prs->t_i) : i(&e, -1);
	else if (e > -1 && (rt->prs->b_o = BO_C) &&
	(rt->prs->b_c = BC_C))
		return (error(rt, 10, 2));
	return (e);
}

static int	add_global_parameters(t_rt *rt, int b_end, int e, char type)
{
	while (e != -1 && rt->prs->i < b_end)
	{
		if ((e = check_balises(rt, BO_N, BC_N)) > 1)
			rt->prs->obj_tmp->n = get_s(rt->prs, e, 7);
		else if (e > -1 && type == 'C' &&
		(e = check_balises(rt, BO_FL, BC_FL)) > 1)
			(get_i(rt, e, BO_FL, BC_FL)) ?
			(rt->prs->obj_tmp->fl = rt->prs->t_i) : i(&e, -1);
		else if (e > -1 && (e = check_balises(rt, BO_CR, BC_CR)) > 1)
			(get_v(rt, e, BO_CR, BC_CR)) ?
			(vc(&rt->prs->obj_tmp->rgb, rt->prs->vec)) : i(&e, -1);
		else if (e > -1 && (e = check_balises(rt, BO_CH, BC_CH)) > 1)
			(get_h(rt, e, BO_CH, BC_CH)) ?
			(h(&rt->prs->obj_tmp->rgb, rt->prs->t_u)) : i(&e, -1);
		else if (e > -1 && (e = check_balises(rt, BO_P, BC_P)) > 1)
			(get_v(rt, e, BO_P, BC_P)) ?
			(vc(&rt->prs->obj_tmp->pos, rt->prs->vec)) : i(&e, -1);
		else if (e > -1 && (e = check_balises(rt, BO_R, BC_R)) > 1)
			(get_v(rt, e, BO_R, BC_R)) ?
			(vc(&rt->prs->obj_tmp->rot, rt->prs->vec)) : i(&e, -1);
		else if (e > -1)
			e = add_element_parameters(rt, 0, type);
	}
	return (e);
}

int			add_element(t_rt *rt, int b_end, int e, char type)
{
	if (type == 'C' && rt->scn->n_cams == N_CAMS)
		e = error(rt, 20, 2);
	else if (type == 'L' && rt->scn->n_lgts == N_LGTS)
		e = error(rt, 21, 2);
	else if (type == 'O' && rt->scn->n_objs == N_OBJS)
		e = error(rt, 22, 2);
	rt->prs->obj_tmp = assign_default_obj_values(rt->prs->obj_tmp, type, 0);
	if (e != -1 && add_global_parameters(rt, b_end, 0, type) != -1)
	{
		if (type == 'C')
			return (check_camera(rt, rt->scn->n_cams));
		else if (type == 'L')
			return (check_light(rt, rt->scn->n_lgts));
		else if (type == 'O')
			return (check_object(rt));
	}
	return (-1);
}
