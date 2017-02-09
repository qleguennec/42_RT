/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 15:28:36 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/02 18:32:59 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_buttons_rect(t_ui *ui)
{
	ui->b_rect[0] = (SDL_Rect){225, 25, 33, 34};
	ui->b_rect[1] = (SDL_Rect){225, 162, 111, 34};
	ui->b_rect[2] = (SDL_Rect){225, 25, 111, 34};
	ui->b_rect[3] = (SDL_Rect){359, 25, 34, 34};
	ui->b_rect[4] = (SDL_Rect){411, 25, 34, 34};
	ui->b_rect[5] = (SDL_Rect){452, 25, 34, 34};
	ui->b_rect[6] = (SDL_Rect){493, 25, 33, 34};
	ui->b_rect[7] = (SDL_Rect){545, 25, 34, 34};
	ui->b_rect[8] = (SDL_Rect){586, 25, 33, 34};
	ui->b_rect[9] = (SDL_Rect){626, 25, 34, 34};
	ui->b_rect[10] = (SDL_Rect){667, 25, 34, 34};
	ui->b_rect[11] = (SDL_Rect){708, 25, 33, 34};
	ui->b_rect[12] = (SDL_Rect){762, 25, 34, 34};
	ui->b_rect[13] = (SDL_Rect){803, 25, 34, 34};
	ui->b_rect[14] = (SDL_Rect){844, 25, 34, 34};
	ui->b_rect[15] = (SDL_Rect){885, 25, 34, 34};
	ui->b_rect[16] = (SDL_Rect){940, 25, 34, 34};
	ui->b_rect[17] = (SDL_Rect){981, 25, 34, 34};
	ui->b_rect[18] = (SDL_Rect){1022, 25, 34, 34};
}

static void	init_buttons_state(t_ui *ui)
{
	ui->b_state[0] = 0;
	ui->b_state[1] = 0;
	ui->b_state[2] = 0;
	ui->b_state[3] = 0;
	ui->b_state[4] = 0;
	ui->b_state[5] = 0;
	ui->b_state[6] = 0;
	ui->b_state[7] = 0;
	ui->b_state[8] = 0;
	ui->b_state[9] = 0;
	ui->b_state[10] = 0;
	ui->b_state[11] = 0;
	ui->b_state[12] = 4;
	ui->b_state[13] = 4;
	ui->b_state[14] = 4;
	ui->b_state[15] = 4;
	ui->b_state[16] = 2;
	ui->b_state[17] = 2;
	ui->b_state[18] = 0;
}

static void	init_buttons(t_rt *rt)
{
	init_buttons_rect(rt->ui);
	init_buttons_state(rt->ui);
	draw_button(rt, 2, 0);
	draw_button(rt, 16, 2);
	draw_button(rt, 17, 2);
	draw_button(rt, 12, 3);
	draw_button(rt, 13, 3);
	draw_button(rt, 14, 3);
	draw_button(rt, 15, 3);
}

static void	init_gui_areas(t_ui *ui, short i)
{
	ui->area[0] = (SDL_Rect){0, 0, 1280, 66};
	ui->area[1] = (SDL_Rect){225, 25, 829, 34};
	ui->area[2] = (SDL_Rect){0, 67, 214, 653};
	ui->area[3] = (SDL_Rect){144, 101, 47, 63};
	ui->area[4] = (SDL_Rect){13, 224, 188, (i * 29) - 1};
	ui->area[7] = (SDL_Rect){1066, 67, 214, 653};
	comment(" v Current Selected Element Area v ");
	ui->area[8] = (SDL_Rect){1075, 77, 195, 422};
	comment(" ^ Current Selected Element Area ^ ");
	ui->area[9] = (SDL_Rect){1084, 625, 12, 68};
	ui->area[10] = (SDL_Rect){0, 690, 215, 30};
	ui->area[11] = (SDL_Rect){1065, 690, 215, 30};
	ui->area[12] = (SDL_Rect){13, 224, 188, (i * 29) - 1};
	ui->ra_rect[0] = (SDL_Rect){1046, 625, 12, 12};
	ui->ra_rect[1] = (SDL_Rect){1046, 643, 12, 12};
	ui->ra_rect[2] = (SDL_Rect){1046, 662, 12, 12};
	ui->ra_rect[3] = (SDL_Rect){1084, 681, 12, 12};
	ui->ra_rect[4] = (SDL_Rect){1084, 662, 12, 12};
	ui->ra_rect[5] = (SDL_Rect){1084, 643, 12, 12};
	ui->ra_rect[6] = (SDL_Rect){1084, 625, 12, 12};
	ui->r_hover = (SDL_Rect){13, 224, 188, 29};
}

void		init_gui_structure(t_rt *rt)
{
	rt->ui->t_c = 0;
	rt->ui->b_down = -1;
	rt->ui->b_hover = -1;
	rt->ui->c_down = -1;
	rt->ui->c_hover = -1;
	rt->ui->ra_down = -1;
	rt->ui->ra_hover = -1;
	rt->ui->save_num = 1;
	rt->ui->m_visible = 0;
	rt->ui->nav_state = 0;
	rt->ui->c_clr[0] = (SDL_Color){47, 47, 47, 255};
	rt->ui->c_clr[1] = (SDL_Color){55, 55, 55, 255};
	rt->ui->c_clr[2] = (SDL_Color){38, 38, 38, 255};
	init_gui_areas(rt->ui, rt->scn->n_elms);
	init_informations(rt, 0);
	SDL_LowerBlit(rt->ui->s_ui, &rt->ui->area[0], rt->s_back, &rt->ui->area[0]);
	SDL_LowerBlit(rt->ui->s_ui, &rt->ui->area[2], rt->s_back, &rt->ui->area[2]);
	SDL_LowerBlit(rt->ui->s_ui, &rt->ui->area[7], rt->s_back, &rt->ui->area[7]);
	SDL_LowerBlit(rt->ui->s_ui, &rt->ui->ra_rect[2], rt->s_back,
	&rt->ui->ra_rect[rt->scn->sp_mode + 3]);
	init_buttons(rt);
	SDL_SetCursor(rt->cursor[0]);
}
