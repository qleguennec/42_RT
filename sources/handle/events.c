/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 19:22:48 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/02 16:50:36 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		handle_events(t_rt *rt)
{
	if (rt->event.window.event == SDL_WINDOWEVENT_CLOSE ||
	(rt->event.type == SDL_KEYDOWN && rt->event.key.keysym.sym == SDLK_ESCAPE))
		rt->run = 0;
	else if (rt->event.type == 0x402 && rt->event.button.button == 1)
		handle_left_click_up(rt);
	else if (rt->event.type == 0x401 && rt->event.button.button == 1 &&
	rt->event.button.clicks == 1)
		handle_left_click_down(rt);
	else if (rt->event.type == 0x401 && rt->event.button.button == 1 &&
	rt->event.button.clicks == 2)
		handle_double_click_down(rt);
	else if (rt->event.type == 0x401 && rt->event.button.button == 3)
		handle_right_click_down(rt);
	else if (rt->event.type == 0x400)
		handle_motion_mouse(rt);
	else if (rt->event.type == 0x300 || rt->event.type == 0x301)
		handle_keyboard(rt);
}
