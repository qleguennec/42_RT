/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene_parameters.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 18:46:35 by bsouchet          #+#    #+#             */
/*   Updated: 2017/04/30 19:41:10 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	draw_parameter_static(t_rt *rt, char *tmp, int y, int mode)
{
	if (mode == 2)
		rt->ui->s_tmp = TTF_RenderText_Shaded(rt->ui->font[1], tmp,
		(SDL_Color){113, 149, 164, 255}, (SDL_Color){42, 52, 64, 255});
	else
		rt->ui->s_tmp = TTF_RenderText_Shaded(rt->ui->font[1], tmp,
		(SDL_Color){109, 125, 145, 255}, (SDL_Color){42, 52, 64, 255});
	SDL_LowerBlit(rt->ui->s_tmp, &(SDL_Rect){0, 0, rt->ui->s_tmp->w,
	rt->ui->s_tmp->h}, rt->s_back, &(SDL_Rect){((rt->ui->area[3].x + 47) -
	(ft_strlen(tmp) * 7)), y,
	rt->ui->s_tmp->w, rt->ui->s_tmp->h});
	SDL_FreeSurface(rt->ui->s_tmp);
	free(tmp);
}

void		draw_scene_parameters(t_rt *rt)
{
	char	*tmp;

	tmp = ft_dtoa(rt->scn->ambient);
	draw_parameter_static(rt, tmp, (rt->ui->area[3].y + 3), 0);
	tmp = ft_itoa(rt->scn->aa);
	draw_parameter_static(rt, tmp, (rt->ui->area[3].y + 30), 0);
	tmp = ft_itoa(rt->scn->m_ref);
	draw_parameter_static(rt, tmp, (rt->ui->area[3].y + 57), 0);
}

void		draw_sp_element(t_rt *rt, int b_num, int mode)
{
	char	*tmp;
	size_t	clr;

	tmp = NULL;
	clr = 0xFF29323e;
	if (mode == 1)
		clr = HOVER_SE;
	else if (mode == 2)
		clr = FOCUS_SE;
	fsdl_draw_rect(rt->s_back, rt->ui->param_b_rect[b_num], clr);
	if (b_num == 0)
		tmp = ft_dtoa(rt->scn->ambient);
	else if (b_num == 1)
		tmp = ft_itoa(rt->scn->aa);
	else if (b_num == 2)
		tmp = ft_itoa(rt->scn->m_ref);
	draw_parameter_static(rt, tmp, rt->ui->param_b_rect[b_num].y + 3, mode);
	(mode == 0) ? (rt->ui->b_sp_hover = -1) : 1;
}
