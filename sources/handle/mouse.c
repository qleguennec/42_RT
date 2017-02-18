/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 15:42:55 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/16 21:44:55 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	check_mouse_areas(t_rt *rt)
{
	if (fsdl_pt_in_rect(&rt->m_pos, rt->ui->area[1]))
		handle_buttons(rt);
	else if (rt->ui->b_state[16] == 2 &&
	fsdl_pt_in_rect(&rt->m_pos, rt->ui->area[4]))
		handle_outliner(rt, 0, 0, 0);
	else if (rt->ui->b_state[17] == 2 &&
	fsdl_pt_in_rect(&rt->m_pos, rt->ui->area[9]))
		handle_special_mode(rt, 3);
}

void		handle_motion_mouse(t_rt *rt)
{
	rt->m_pos.x = rt->event.motion.x;
	rt->m_pos.y = rt->event.motion.y;
	if (rt->ui->ra_hover != -1 &&
	fsdl_pt_in_rect(&rt->m_pos, rt->ui->ra_rect[(int)rt->ui->ra_hover]))
		return ;
	else if (rt->ui->ra_hover != -1)
		draw_special_mode(rt, rt->ui->ra_hover, 0);
	if (rt->ui->c_hover > -1 && fsdl_pt_in_rect(&rt->m_pos, RECT_OUTLINER))
		return ;
	else if (rt->ui->c_hover > -1)
		draw_outliner_element(rt, rt->ui->c_elem, 0);
	if (rt->ui->c_hover < -1 && fsdl_pt_in_rect(&rt->m_pos, rt->ui->r_hover))
		return ;
	else if (rt->ui->c_hover < -1)
		draw_nav_element(rt, 0);
	if (rt->ui->b_hover != -1 &&
		fsdl_pt_in_rect(&rt->m_pos, rt->ui->b_rect[(int)rt->ui->b_hover]))
		return ;
	else if (rt->ui->b_hover != -1 && rt->ui->b_state[(int)rt->ui->b_hover] < 2)
		draw_button(rt, rt->ui->b_hover, 0);
	else if (rt->ui->b_hover != -1 && rt->ui->b_state[(int)rt->ui->b_hover] == 2
	&& !fsdl_pt_in_rect(&rt->m_pos, rt->ui->b_rect[(int)rt->ui->b_hover]) &&
		(rt->ui->b_hover = -1) != 0)
		SDL_SetCursor(rt->cursor[0]);
	check_mouse_areas(rt);
}
