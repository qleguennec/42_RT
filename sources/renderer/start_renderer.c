/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_renderer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 11:13:35 by bsouchet          #+#    #+#             */
/*   Updated: 2017/04/26 15:39:49 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			add_render_frame(t_rt *rt)
{
	SDL_LowerBlit(rt->s_rend, &(SDL_Rect){(rt->r_view.x - 18), 0, rt->r_view.w,
	rt->r_view.h}, rt->s_back, &rt->r_view);
	return (1);
}

static int	global_loop(t_rt *rt, t_cl *cl)
{
	while (rt->run)
	{
		if (SDL_PollEvent(&rt->event))
			handle_events(rt, cl);
		SDL_UpdateWindowSurface(rt->win);
		fsdl_fps_limit(rt->fps);
		fsdl_fps_counter(rt->fps);
	}
	return (free_elements(rt));
}

int			create_window(t_rt *rt, t_cl *cl)
{
	TTF_Init();
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
		return (error(rt, 29));
	if (!(rt->w_icon = IMG_Load(WIN_ICON)))
		return (error(rt, 32));
	rt->w_title = ft_strjoin(WIN_TITLE, (char *)rt->scn->name, 'N');
	if (!(rt->win = SDL_CreateWindow(rt->w_title, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, 0)))
		return (error(rt, 30));
	SDL_SetWindowIcon(rt->win, rt->w_icon);
	free(rt->w_title);
	init_renderer(rt);
	if (!(cl_main_krl_update_buffers(cl, rt->scn)
		&& cl_main_krl_update_camera(cl, rt->scn->c_cam)
		&& cl_main_krl_exec(cl)
		&& cl_copy_image_buffer(cl, rt->s_rend->pixels)))
		return (error(rt, 42));
	cluster_init(cl);
	add_render_frame(rt);
	return (global_loop(rt, cl));
}
