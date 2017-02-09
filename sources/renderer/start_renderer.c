/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_renderer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 11:13:35 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/08 13:00:15 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	add_render_frame(t_rt *rt)
{
	SDL_LowerBlit(rt->s_rend, &(SDL_Rect){(rt->r_view.x - 18), 0, rt->r_view.w,
	rt->r_view.h}, rt->s_back, &rt->r_view);
	rt->render = 0;
	return (1);
}

static int	global_loop(t_rt *rt)
{
	while (rt->run)
	{
		if (SDL_PollEvent(&rt->event))
			handle_events(rt);
		(rt->render) ? add_render_frame(rt) : 1;
		SDL_UpdateWindowSurface(rt->win);
		fsdl_fps_limit(rt->fps);
		fsdl_fps_counter(rt->fps);
	}
	return (free_elements(rt));
}

int			create_window(t_rt *rt)
{
	TTF_Init();
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
		return (error(rt, 29, 2));
	if (!(rt->w_icon = IMG_Load(WIN_ICON)))
		return (error(rt, 32, 2));
	rt->w_title = ft_strjoin(WIN_TITLE, rt->scn->name, 'N');
	if (!(rt->win = SDL_CreateWindow(rt->w_title, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, 0)))
		return (error(rt, 30, 2));
	SDL_SetWindowIcon(rt->win, rt->w_icon);
	free(rt->w_title);
	init_renderer(rt);
	return (global_loop(rt));
}
