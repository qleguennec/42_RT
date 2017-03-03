/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 17:08:04 by bsouchet          #+#    #+#             */
/*   Updated: 2017/03/03 18:43:53 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	handle_keyboard_se(t_rt *rt, t_cl *cl)
{
	static int	num = 0;

	++num;
	if (CK_DW == SDLK_KP_ENTER || CK_DW == SDLK_RETURN ||
	CK_DW == SDLK_RETURN2 || CK_DW == SDLK_END)
	{
		if (fsdl_pt_in_rect(&rt->m_pos, *rt->ui->case_rect))
			draw_se_button(rt, rt->ui->case_active, rt->scn->s_elem->type, 1);
		else
			draw_se_button(rt, rt->ui->case_active, rt->scn->s_elem->type, 4);
		rt->ui->case_active = -1;
		rt->ui->case_rect = NULL;
		return (1);
	}
	if (num & 1)
		return (1);
	if (CK_DW == SDLK_EQUALS || CK_DW == SDLK_KP_PLUS || CK_DW == SDLK_UP)
		update_se_box_plus(rt, cl);
	if (CK_DW == SDLK_MINUS || CK_DW == SDLK_KP_MINUS || CK_DW == SDLK_DOWN)
		update_se_box_minus(rt, cl);
	return (1);
}

static int	handle_se(t_rt *rt, t_cl *cl)
{
	(void)rt;
	(void)cl;
	return (1);
}

static int	handle_camera(t_rt *rt, t_cl *cl)
{
	(void)rt;
	(void)cl;
	return (1);
}

int			handle_keyboard(t_rt *rt, t_cl *cl)
{
	if (rt->ui->case_active > 0)
		return (handle_keyboard_se(rt, cl));
	else if (rt->scn->s_elem)
		return (handle_se(rt, cl));
	return (handle_camera(rt, cl));
}
