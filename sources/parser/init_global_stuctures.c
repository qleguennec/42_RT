/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_global_stuctures.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 13:55:32 by bsouchet          #+#    #+#             */
/*   Updated: 2017/01/29 18:11:58 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Functions to initilize all elements (cameras, lights, objects) of the scene
*/

void	init_elements(t_rt *rt)
{
	rt->prs->t_i = 0;
	rt->scn->ambient = 0.2;
	rt->scn->aa = 2;
	rt->scn->m_ref = 1;
	rt->scn->name = NULL;
	rt->scn->n_cams = 0;
	rt->scn->n_lgts = 0;
	rt->scn->n_objs = 0;
	rt->scn->sp_mode = 0;
	rt->scn->o = NULL;
	while (rt->prs->t_i < 6)
		rt->scn->t[rt->prs->t_i++] = 0;
	rt->prs->t_i = 0;
}

int		init_structures(t_rt *rt)
{
	if (!(rt->prs = (t_parser *)malloc(sizeof(t_parser))))
		return (error(rt, 0, 1));
	if (!(rt->scn = (t_scene *)malloc(sizeof(t_scene))))
		return (error(rt, 0, 1));
	if (!(rt->ui = (t_ui *)malloc(sizeof(t_ui))))
		return (error(rt, 0, 1));
	if (!(rt->fps = (t_timer *)malloc(sizeof(t_timer))))
		return (error(rt, 0, 1));
	if (!(rt->prs->obj_tmp = (t_obj *)malloc(sizeof(t_obj))))
		return (error(rt, 0, 1));
	if (!(rt->cursor = (SDL_Cursor **)malloc(sizeof(SDL_Cursor *) * 2)))
		return (error(rt, 0, 1));
	if (!(rt->ui->font = (TTF_Font **)malloc(sizeof(TTF_Font *) * 2)))
		return (error(rt, 0, 1));
	init_elements(rt);
	rt->prs->i = 0;
	rt->prs->copy = 1;
	ft_short_bzero(rt->prs->n, 50);
	return (0);
}
