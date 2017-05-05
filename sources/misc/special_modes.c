/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_modes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 17:30:10 by bsouchet          #+#    #+#             */
/*   Updated: 2017/05/02 19:25:21 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		add_sepia_effect(t_rt *rt)
{
	rt->ui->t_rect.y = -1;
	while (++rt->ui->t_rect.y < rt->s_rend->h)
	{
		rt->ui->t_rect.x = -1;
		while (++rt->ui->t_rect.x < rt->s_rend->w)
		{
			rt->ui->t_v =
			fsdl_get_pt_clr(rt->s_rend, rt->ui->t_rect.x, rt->ui->t_rect.y);
			fsdl_draw_pt(rt->s_effct,
			((((unsigned)((rt->ui->t_v.z * 0.393) + (rt->ui->t_v.y * 0.769) +
			(rt->ui->t_v.x * 0.189)) & 0xFF) << 24) +
			(((unsigned)((rt->ui->t_v.z * 0.349) + (rt->ui->t_v.y * 0.686) +
			(rt->ui->t_v.x * 0.168)) & 0xFF) << 16) +
			(((unsigned)((rt->ui->t_v.z * 0.272) + (rt->ui->t_v.y * 0.534) +
			(rt->ui->t_v.x * 0.131)) & 0xFF) << 8) +
			((unsigned)255 & 0xff)), rt->ui->t_rect.x, rt->ui->t_rect.y);
		}
	}
}

void		add_black_n_white_effect(t_rt *rt)
{
		rt->ui->t_rect.y = -1;
	while (++rt->ui->t_rect.y < rt->s_rend->h)
	{
		rt->ui->t_rect.x = -1;
		while (++rt->ui->t_rect.x < rt->s_rend->w)
		{
			rt->ui->t_v =
			fsdl_get_pt_clr(rt->s_rend, rt->ui->t_rect.x, rt->ui->t_rect.y);
			fsdl_draw_pt(rt->s_effct, ((((unsigned)((rt->ui->t_v.z * 0.1140) +
			(rt->ui->t_v.y * 0.5870) + (rt->ui->t_v.x * 0.2989)) & 0xFF)
			<< 24) + (((unsigned)((rt->ui->t_v.z * 0.1140) + 
			(rt->ui->t_v.y * 0.5870) + (rt->ui->t_v.x * 0.2989)) & 0xFF)
			<< 16) + (((unsigned)((rt->ui->t_v.z * 0.1140) +
			(rt->ui->t_v.y * 0.5870) + (rt->ui->t_v.x * 0.2989)) & 0xFF)
			<< 8) + ((unsigned)255 & 0xff)),
			rt->ui->t_rect.x, rt->ui->t_rect.y);
		}
	}
}

void		add_cartoon_effect(t_rt *rt)
{
	(void)rt;
}
