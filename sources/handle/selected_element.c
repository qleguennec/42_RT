/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selected_element.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 21:18:20 by bsouchet          #+#    #+#             */
/*   Updated: 2017/03/01 20:11:18 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			delete_current_element(t_rt *rt, t_cl *cl,
				t_obj *nav, t_obj *tmp)
{
	char		*str;

	if ((rt->scn->s_elem->type == 'C' && rt->scn->n_cams == 1) ||
		(rt->scn->s_elem->type == 'L' && rt->scn->n_lgts == 1) ||
		(rt->scn->s_elem->type == 'O' && rt->scn->n_objs == 1))
	{
		set_default_element(rt, cl, rt->scn->s_elem->type);
		return ;
	}
	if (rt->scn->s_elem->type == 'C')
		--rt->scn->n_cams;
	else
		(rt->scn->s_elem->type == 'L') ? --rt->scn->n_lgts : --rt->scn->n_objs;
	--rt->scn->n_elms;
	if (rt->scn->s_elem->type != 'C')
		(rt->scn->s_elem->type == 'L') ? --rt->scn->lt[rt->scn->s_elem->forme] :
		--rt->scn->ot[rt->scn->s_elem->forme];
	nav = rt->scn->o;
	while (nav->next && nav->next->id != rt->scn->s_elem->id)
		nav = nav->next;
	tmp = nav->next;
	nav->next = nav->next->next;
	str = (char *)tmp->n;
	free(tmp);
	redraw_current_element(rt, cl, str);
}

void			handle_selected_element_down(t_rt *rt, t_cl *cl)
{
	if (rt->ui->b_se_hover == 0)
	{
		delete_current_element(rt, cl, NULL, NULL);
		rt->ui->b_se_down = -1;
		rt->ui->b_se_hover = -1;
		return ;
	}
	rt->ui->b_se_down = rt->ui->b_se_hover;
	rt->ui->case_active = rt->ui->b_se_hover;
	draw_se_button(rt, rt->ui->b_se_hover, rt->scn->s_elem->type, 2);
	redraw_case_active(rt, 1);
	rt->ui->case_rect = rt->ui->b_se_rect;
}

static void		handle_selected_camera(t_rt *rt)
{
	rt->ui->t_c = 0;
	while (rt->ui->t_c < 8 &&
	!fsdl_pt_in_rect(&rt->m_pos, rt->ui->cam_b_rect[(int)rt->ui->t_c]))
		rt->ui->t_c++;
	if ((rt->ui->t_c == 8 || rt->ui->t_c == rt->ui->case_active) &&
	(rt->ui->b_se_hover = -1) != 0)
		return ;
	rt->ui->b_se_hover = rt->ui->t_c;
	draw_se_button(rt, rt->ui->b_se_hover, 'C', 1);
}

static void		handle_selected_light(t_rt *rt)
{
	rt->ui->t_c = 0;
	while (rt->ui->t_c < 12 &&
	!fsdl_pt_in_rect(&rt->m_pos, rt->ui->lgt_b_rect[(int)rt->ui->t_c]))
		rt->ui->t_c++;
	if ((rt->ui->t_c == 12 || rt->ui->t_c == rt->ui->case_active) &&
	(rt->ui->b_se_hover = -1) != 0)
		return ;
	rt->ui->b_se_hover = rt->ui->t_c;
	draw_se_button(rt, rt->ui->b_se_hover, 'L', 1);
}

static void		handle_selected_object(t_rt *rt)
{
	rt->ui->t_c = 0;
	while (rt->ui->t_c < 18 &&
	!fsdl_pt_in_rect(&rt->m_pos, rt->ui->obj_b_rect[(int)rt->ui->t_c]))
		rt->ui->t_c++;
	if ((rt->ui->t_c == 18 || rt->ui->t_c == rt->ui->case_active) &&
	(rt->ui->b_se_hover = -1) != 0)
		return ;
	rt->ui->b_se_hover = rt->ui->t_c;
	draw_se_button(rt, rt->ui->b_se_hover, 'O', 1);
}

void			handle_selected_element(t_rt *rt)
{
	if (rt->scn->s_elem->type == 'C' &&
	fsdl_pt_in_rect(&rt->m_pos, rt->ui->area[14]))
		handle_selected_camera(rt);
	else if (rt->scn->s_elem->type == 'L' &&
	fsdl_pt_in_rect(&rt->m_pos, rt->ui->area[15]))
		handle_selected_light(rt);
	else if (rt->scn->s_elem->type == 'O')
		handle_selected_object(rt);
}