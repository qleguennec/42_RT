/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 15:37:49 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/16 11:50:36 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		draw_special_mode(t_rt *rt, int r_num, int type)
{
	SDL_LowerBlit(rt->ui->s_ui, &rt->ui->ra_rect[type], rt->s_back,
	&rt->ui->ra_rect[r_num]);
	(type == 0) ? (rt->ui->ra_hover = -1) : 1;
	SDL_SetCursor(rt->cursor[(type == 1) ? 1 : 0]);
}

void		draw_materials(t_rt *rt, char type)
{
	if (type == 'E')
	{
		rt->ui->b_state[12] = 0;
		rt->ui->b_state[13] = 0;
		rt->ui->b_state[14] = 0;
		rt->ui->b_state[15] = 0;
		draw_button(rt, 12, 0);
		draw_button(rt, 13, 0);
		draw_button(rt, 14, 0);
		draw_button(rt, 15, 0);
	}
	else
	{
		rt->ui->b_state[12] = 4;
		rt->ui->b_state[13] = 4;
		rt->ui->b_state[14] = 4;
		rt->ui->b_state[15] = 4;
		draw_button(rt, 12, 3);
		draw_button(rt, 13, 3);
		draw_button(rt, 14, 3);
		draw_button(rt, 15, 3);
	}
	rt->ui->m_visible = (type == 'E') ? 1 : 0;
}

void		draw_selected_element(t_rt *rt)
{
	if (rt->scn->s_elem->type == 'C')
		fsdl_fill_rect(rt->s_back, rt->ui->area[8], WHITE_BG);
	else if (rt->scn->s_elem->type == 'L')
		fsdl_fill_rect(rt->s_back, rt->ui->area[8], YELLOW_BG);
	else if (rt->scn->s_elem->type == 'O')
		fsdl_fill_rect(rt->s_back, rt->ui->area[8], BLUE_BG);
}

void		draw_current_camera_name(t_rt *rt, short type)
{
	fsdl_fill_rect(rt->s_back, (SDL_Rect){1078, 32, 190, 16}, PAN_BG);
	if (type == 2)
		free(rt->ui->r_dim);
	if (type != 0)
		free(rt->ui->c_name);
	if (type != 1)
		rt->ui->r_dim = ft_strjoin(ft_strjoin(ft_strjoin(" (",
		ft_itoa(rt->r_view.w), 'R'), ft_strjoin(" x ",
		ft_itoa(rt->r_view.h), 'R'), 'B'), ")", 'L');
	rt->ui->c_name = ft_strunc((char *)rt->scn->c_cam->n,
	(24 - ft_strlen(rt->ui->r_dim)));
	rt->ui->tmp = ft_strjoin(rt->ui->c_name, rt->ui->r_dim, 'N');
	rt->ui->s_tmp = TTF_RenderText_Shaded(rt->ui->font[0], rt->ui->tmp,
	(SDL_Color){162, 162, 162, 255}, (SDL_Color){53, 53, 53, 255});
	rt->ui->t_c = ((192 - rt->ui->s_tmp->w) / 2);
	SDL_LowerBlit(rt->ui->s_tmp, &(SDL_Rect){0, 0, rt->ui->s_tmp->w,
	rt->ui->s_tmp->h}, rt->s_back, &(SDL_Rect){1078 + rt->ui->t_c, 32,
	rt->ui->s_tmp->w, rt->ui->s_tmp->h});
	SDL_FreeSurface(rt->ui->s_tmp);
	free(rt->ui->tmp);
}

void		draw_button(t_rt *rt, int b_num, int type)
{
	if (b_num == 2)
		rt->ui->t_rect = rt->ui->b_rect[1];
	else
		rt->ui->t_rect = rt->ui->b_rect[b_num];
	(type == 1) ? rt->ui->t_rect.y += 51 : 1;
	(type == 2) ? rt->ui->t_rect.y += 94 : 1;
	(type == 3) ? rt->ui->t_rect.y += 137 : 1;
	SDL_LowerBlit(rt->ui->s_ui, &rt->ui->t_rect, rt->s_back,
	&rt->ui->b_rect[b_num]);
	(type == 0) ? (rt->ui->b_hover = -1) : 1;
	SDL_SetCursor(rt->cursor[(type == 1 || type == 2) ? 1 : 0]);
}
