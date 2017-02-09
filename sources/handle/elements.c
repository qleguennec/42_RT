/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 17:56:13 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/08 14:00:49 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		add_new_element(t_rt *rt, char type)
{
	draw_button(rt, 2, -1);
	rt->prs->obj_tmp = assign_default_obj_values(rt->prs->obj_tmp, type, 0);
	if (type == 'C')
	{
		rt->prs->obj_tmp->n =
		ft_strjoin("Camera ", ft_itoa(rt->scn->n_cams), 'R');
		rt->scn->o = lst_new_camera(rt, rt->scn->o, 1);
	}
	else if (type == 'L')
	{
		rt->prs->obj_tmp->n =
		ft_strjoin("Light ", ft_itoa(rt->scn->n_lgts), 'R');
		rt->scn->o = lst_new_light(rt, rt->scn->o, 1);
	}
	else if (type == 'O')
	{
		rt->prs->obj_tmp->n =
		ft_strjoin("Object ", ft_itoa(rt->scn->n_objs), 'R');
		rt->scn->o = lst_new_object(rt, rt->scn->o, 1);
	}
	rt->ui->area[4].h += 29;
	if (rt->scn->n_elms >= 15)
		rt->ui->nav_state = 1;
	(rt->r_view.x != 18) ? draw_outliner(rt, -1, 0) : 1;
}
