/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 17:08:04 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/28 22:08:37 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		handle_keyboard_se(t_rt *rt, t_cl *cl)
{
	if (CK_DOWN == SDLK_KP_ENTER || CK_DOWN == SDLK_RETURN ||
	CK_DOWN == SDLK_RETURN2 || CK_DOWN == SDLK_END)
	{
		if (fsdl_pt_in_rect(&rt->m_pos, *rt->ui->case_rect))
			draw_se_button(rt, rt->ui->case_active, rt->scn->s_elem->type, 1);
		else
			draw_se_button(rt, rt->ui->case_active, rt->scn->s_elem->type, 4);
		rt->ui->case_active = -1;
		rt->ui->case_rect = NULL;
	}
	if (CK_DOWN == SDLK_EQUALS || CK_DOWN == SDLK_KP_PLUS)
		update_se_box_plus(rt, cl);
	if (CK_DOWN == SDLK_MINUS || CK_DOWN == SDLK_KP_MINUS)
		update_se_box_minus(rt, cl);
}

void		handle_keyboard(t_rt *rt, t_cl *cl)
{
	if (rt->ui->case_active > 0)
	{
		handle_keyboard_se(rt, cl);
		return ;
	}
}
