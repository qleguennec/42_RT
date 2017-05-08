/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saturate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 21:08:49 by bsouchet          #+#    #+#             */
/*   Updated: 2017/05/06 22:44:30 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	add_saturate_effect(t_rt *rt)
{
	rt->ui->t_rect.y = -1;
	while (++rt->ui->t_rect.y < rt->s_rend->h)
	{
		rt->ui->t_rect.x = -1;
		while (++rt->ui->t_rect.x < rt->s_rend->w)
		{
			rt->ui->t_v =
			fsdl_get_pt_clr(rt->s_rend, rt->ui->t_rect.x, rt->ui->t_rect.y);
			rt->ui->hsv = ft_vec_to_hsv(rt->ui->t_v);
			rt->ui->hsv.s += ((rt->ui->hsv.s * 30.0f) / 100.0f);
			if (rt->ui->hsv.s > 1.0f)
				rt->ui->hsv.s = 1.0f;
			rt->ui->t_v = ft_hsv_to_rgb(rt->ui->hsv);
			//printf("%f -- %f -- %f\n", rt->ui->t_v.x, rt->ui->t_v.y, rt->ui->t_v.z);
			fsdl_draw_pt(rt->s_effct, ((((unsigned)rt->ui->t_v.x & 0xFF)
			<< 24) + (((unsigned)rt->ui->t_v.y & 0xFF)
			<< 16) + (((unsigned)rt->ui->t_v.z & 0xFF)
			<< 8) + ((unsigned)255 & 0xff)),
			rt->ui->t_rect.x, rt->ui->t_rect.y);
		}
	}
}
