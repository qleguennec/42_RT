/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_outliner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 18:43:06 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/08 15:14:02 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

size_t		fsdl_clr_to_size_t(SDL_Color clr)
{
	size_t	new;

	new = 0;
	if (clr.r == 47)
		new = 0xFF2f2f2f;
	else if (clr.r == 55)
		new = 0xFF373737;
	else if (clr.r == 38)
		new = 0xFF262626;
	return (new);
}

void		draw_outliner_element(t_rt *rt, t_obj *obj, int state)
{
	int		t;
	char	*tmp;

	t = (obj->next == NULL || obj->t != obj->next->t) ? 282 : 253;
	t += (state > 0) ? 58 : 0;
	t += (state > 1) ? 58 : 0;
	SDL_LowerBlit(rt->ui->s_ui, &(SDL_Rect){13, t, obj->r_ol.w, 29},
	rt->s_back, &(SDL_Rect){13, obj->r_ol.y, obj->r_ol.w, 29});
	tmp = ft_strunc(obj->n, 21);
	if (obj->v == 1)
		fsdl_fill_rect(rt->s_back, (SDL_Rect){173, obj->r_ol.y + 8, 15, 13},
		fsdl_clr_to_size_t(rt->ui->c_clr[state]));
	rt->ui->s_tmp = TTF_RenderText_Shaded(rt->ui->font[1], tmp,
	(SDL_Color){162, 162, 162, 255}, rt->ui->c_clr[state]);
	free(tmp);
	SDL_LowerBlit(rt->ui->s_tmp, &(SDL_Rect){0, 0, rt->ui->s_tmp->w,
	rt->ui->s_tmp->h}, rt->s_back, &(SDL_Rect){45, obj->r_ol.y + 7,
	rt->ui->s_tmp->w, rt->ui->s_tmp->h});
	SDL_FreeSurface(rt->ui->s_tmp);
	if (state == 0)
		rt->ui->c_hover = -1;
	SDL_SetCursor(rt->cursor[1]);
}

static void	draw_outliner_title(t_rt *rt, int i)
{
	char	*name;

	if (i == -1)
		name = (rt->scn->n_cams > 2) ? "Cameras" : "Camera";
	else if (i == -2)
		name = (rt->scn->n_lgts > 2) ? "Lights" : "Light";
	else
		name = (rt->scn->n_objs > 2) ? "Objects" : "Object";
	SDL_LowerBlit(rt->ui->s_ui, &(SDL_Rect){13, 224, rt->ui->area[12].w, 29},
	rt->s_back, &(SDL_Rect){13, rt->ui->area[12].y, rt->ui->area[12].w, 29});
	rt->ui->s_tmp = TTF_RenderText_Shaded(rt->ui->font[1], name,
	(SDL_Color){162, 162, 162, 255}, (SDL_Color){43, 43, 43, 255});
	SDL_LowerBlit(rt->ui->s_tmp, &(SDL_Rect){0, 0, rt->ui->s_tmp->w,
	rt->ui->s_tmp->h}, rt->s_back, &(SDL_Rect){32, rt->ui->area[12].y + 7,
	rt->ui->s_tmp->w, rt->ui->s_tmp->h});
	SDL_FreeSurface(rt->ui->s_tmp);
}

void		draw_top_nav_button(t_rt *rt, int state)
{
	if (state == -1)
		state = 536;
	else if (state == 0)
		state = 552;
	else if (state == 1)
		state = 568;
	SDL_LowerBlit(rt->ui->s_ui, &(SDL_Rect){13, state, 188, 16},
	rt->s_back, &(SDL_Rect){13, 223, 188, 16});
	rt->ui->area[12].y += 15;
}

void		draw_bottom_nav_button(t_rt *rt, int state)
{
	if (state == -1)
		state = 584;
	else if (state == 0)
		state = 600;
	else if (state == 1)
		state = 616;
	SDL_LowerBlit(rt->ui->s_ui, &(SDL_Rect){13, state, 188, 16},
	rt->s_back, &(SDL_Rect){13, 616, 188, 16});
}

void		draw_nav_element(t_rt *rt, int state)
{
	int		pos;
	t_obj	*list;

	list = rt->scn->b_outliner;
	if (rt->ui->c_hover == -2)
	{
		if (rt->scn->b_outliner->n == NULL && rt->scn->b_outliner->t == 'C')
			state = -1;
		draw_top_nav_button(rt, state);
	}
	else
	{
		pos = 13;
		while (--pos)
			list = list->next;
		if (list->next == NULL)
			state = -1;
		draw_bottom_nav_button(rt, state);
	}
	rt->ui->c_hover = -1;
	rt->ui->c_elem = NULL;
	rt->ui->r_hover = (SDL_Rect){0, 0, 0, 0};
}

void		draw_outliner(t_rt *rt, int i, int max)
{
	t_obj	*list;

	list = rt->scn->b_outliner;
	rt->ui->area[12].y = 224;
	fsdl_fill_rect(rt->s_back, (SDL_Rect){13, 224, 188, 409}, INFO_BG);
	if (rt->ui->nav_state == 1)
		draw_top_nav_button(rt, (list->id == rt->scn->o->id) ? -1 : 0);
	max = (rt->ui->nav_state == 1) ? 12 : 13;
	while (i < max && list)
	{
		if (list->title != 0)
			draw_outliner_title(rt, list->title);
		else
		{
			list->r_ol = rt->ui->area[12];
			list->r_ol.h = 29;
			draw_outliner_element(rt, list, 0);
		}
		rt->ui->area[12].y += 29;
		if (i < max - 1)
			list = list->next;
		i++;
	}
	if (rt->ui->nav_state == 1)
		draw_bottom_nav_button(rt, (list->next == NULL) ? -1 : 0);
}
