/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 15:42:55 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/02 19:32:27 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		handle_double_click_down(t_rt *rt)
{
	if (rt->ui->c_down != -1 || rt->ui->c_hover == -1 || rt->ui->c_hover == 'C'
	|| rt->ui->c_elem == rt->scn->c_cam)
		return ;
	rt->n_info = -2;
	rt->scn->c_cam = rt->ui->c_elem;
	draw_current_camera_name(rt, 1);
	rt->ui->tmp = ft_strf(INF33, rt->scn->c_cam->n);
	draw_info_bar(rt);
	free(rt->ui->tmp);
}

void		handle_left_click_up(t_rt *rt)
{
	if (rt->ui->b_down == -1 && rt->ui->c_down == -1 && rt->ui->ra_down == -1)
		return ;
	if (rt->ui->b_down != -1 && rt->ui->b_state[(int)rt->ui->b_down] < 2 &&
		fsdl_pt_in_rect(&rt->m_pos, rt->ui->b_rect[(int)rt->ui->b_down]))
		draw_button(rt, rt->ui->b_down, 1);
	if (rt->ui->c_down > -1 &&
	fsdl_pt_in_rect(&rt->m_pos, rt->ui->c_elem->r_ol))
		draw_outliner_element(rt, rt->ui->c_elem, 1);
	if (rt->ui->ra_down != -1 &&
	fsdl_pt_in_rect(&rt->m_pos, rt->ui->ra_rect[(int)rt->ui->ra_down + 3]))
		draw_special_mode(rt, rt->ui->ra_down, 1);
	if (rt->ui->ra_down != -1)
		SDL_SetCursor(rt->cursor[0]);
	rt->ui->b_down = -1;
	rt->ui->c_down = -1;
	rt->ui->ra_down = -1;
}

void		handle_left_click_down(t_rt *rt)
{
	rt->n_info = -1;
	draw_info_bar(rt);
	rt->ui->t_c = rt->ui->b_state[(int)rt->ui->b_hover];
	if (rt->ui->b_down == -1 && rt->ui->b_hover != -1 && rt->ui->t_c < 3)
		handle_buttons_down(rt);
	else if (rt->ui->c_down == -1 && rt->ui->c_hover != -1)
		handle_outliner_down(rt);
	else if (rt->ui->ra_down == -1 && rt->ui->ra_hover != -1)
		handle_special_modes_down(rt);
}

void		handle_right_click_down(t_rt *rt)
{
	if (rt->ui->c_down != -1 || rt->ui->c_hover == -1 ||
	rt->ui->c_elem->t == 'C')
		return ;
	rt->n_info = -2;
	if (rt->ui->c_elem->v == 0)
	{
		rt->ui->c_elem->v = 1;
		rt->ui->tmp = ft_strf(INF35, rt->ui->c_elem->n);
	}
	else if ((rt->ui->c_elem->v = 0) != -1)
		rt->ui->tmp = ft_strf(INF34, rt->ui->c_elem->n);
	draw_outliner_element(rt, rt->ui->c_elem, 1);
	draw_info_bar(rt);
	free(rt->ui->tmp);
}

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
