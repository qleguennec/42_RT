/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 15:56:06 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/08 16:34:23 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		handle_buttons_down(t_rt *rt)
{
	if (rt->ui->t_c < 2)
		draw_button(rt, rt->ui->b_hover, 2);
	if (rt->ui->t_c == 0)
		execute_button(rt, rt->ui->b_hover);
	if (rt->ui->t_c == 1 && (rt->ui->b_state[(int)rt->ui->b_hover] += 1) != 0)
		draw_panel(rt, rt->ui->b_hover, 1);
	else if (rt->ui->t_c == 2 &&
	(rt->ui->b_state[(int)rt->ui->b_hover] -= 1) != 0)
		draw_panel(rt, rt->ui->b_hover, 0);
	rt->ui->b_down = rt->ui->b_hover;
}

void		edit_buttons_state(t_rt *rt, int i)
{
	(void)i;
	if (rt->scn->n_cams == N_CAMS)
	{
		rt->ui->b_state[3] = 4;
		draw_button(rt, 3, 3);
	}
	if (rt->scn->n_lgts == N_LGTS)
	{
		rt->ui->b_state[4] = 4;
		rt->ui->b_state[5] = 4;
		rt->ui->b_state[6] = 4;
		draw_button(rt, 4, 3);
		draw_button(rt, 5, 3);
		draw_button(rt, 6, 3);
	}
}

void		execute_button(t_rt *rt, int button)
{
	if (button == 2 && (rt->n_info = -1) != 0)
		;
	if (button == 3 && (rt->n_info = 1) != 0)
		add_new_element(rt, 'C');
	else if (button == 4 && (rt->n_info = 2) != 0)
		add_new_element(rt, 'L');
	else if (button == 5 && (rt->n_info = 3) != 0)
		add_new_element(rt, 'L');
	else if (button == 6 && (rt->n_info = 4) != 0)
		add_new_element(rt, 'L');
	else if (button >= 7 && button <= 11 && (rt->n_info = (button - 2)) != 0)
		add_new_element(rt, 'O');
	else if (button >= 12 && button <= 15 && (rt->n_info = (button + 2)) != 0)
		printf("Assign a Shader to the current selected object.\n");
	else if (button == 18 && (rt->n_info = 21) != 0)
		save_to_png(rt);
	edit_buttons_state(rt, 0);
	draw_info_bar(rt);
}

static int	check_buttons(t_rt *rt)
{
	rt->ui->t_c = 2;
	while (rt->ui->t_c < 19 &&
	!fsdl_pt_in_rect(&rt->m_pos, rt->ui->b_rect[(int)rt->ui->t_c]))
		rt->ui->t_c++;
	rt->ui->b_hover = (rt->ui->t_c == 19) ? -1 : rt->ui->t_c;
	return (rt->ui->b_hover);
}

void		handle_buttons(t_rt *rt)
{
	if (check_buttons(rt) == -1)
		return ;
	if (rt->ui->b_state[(int)rt->ui->b_hover] < 2)
		draw_button(rt, rt->ui->b_hover, 1);
	else if (rt->ui->b_hover == 16 || rt->ui->b_hover == 17)
		SDL_SetCursor(rt->cursor[1]);
}
