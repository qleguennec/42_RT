/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_outliner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 18:43:06 by bsouchet          #+#    #+#             */
/*   Updated: 2017/05/08 19:39:21 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		draw_outliner(t_rt *rt, int i, int max)
{
	t_obj	*list;

	list = rt->scn->b_outliner;
	rt->ui->area[12].y = 233;
	fsdl_fill_rect(rt->s_back, (SDL_Rect){13, 233, 188, 409}, INFO_BG);
	(rt->scn->n_elms >= 12) ? (rt->ui->nav_state = 1) : 1;
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
