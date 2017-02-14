/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene_parameters.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 18:46:35 by bsouchet          #+#    #+#             */
/*   Updated: 2017/01/30 20:01:51 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	draw_parameter(t_rt *rt, char *tmp, int y)
{
	rt->ui->s_tmp = TTF_RenderText_Shaded(rt->ui->font[1], tmp,
	(SDL_Color){162, 162, 162, 255}, (SDL_Color){39, 39, 39, 255});
	SDL_LowerBlit(rt->ui->s_tmp, &(SDL_Rect){0, 0, rt->ui->s_tmp->w,
	rt->ui->s_tmp->h}, rt->s_back, &(SDL_Rect){((rt->ui->area[3].x + 42) -
	(ft_strlen(tmp) * 7)), y,
	rt->ui->s_tmp->w, rt->ui->s_tmp->h});
	SDL_FreeSurface(rt->ui->s_tmp);
	free(tmp);
}

void		draw_scene_parameters(t_rt *rt)
{
	char	*tmp;

	tmp = ft_dtoa(rt->scn->ambient);
	draw_parameter(rt, tmp, (rt->ui->area[3].y + 2));
	tmp = ft_itoa(rt->scn->aa);
	draw_parameter(rt, tmp, (rt->ui->area[3].y + 24));
	tmp = ft_itoa(rt->scn->m_ref);
	draw_parameter(rt, tmp, (rt->ui->area[3].y + 46));
}
