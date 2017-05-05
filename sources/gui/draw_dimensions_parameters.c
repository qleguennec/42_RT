/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_dimensions_parameters.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 15:02:08 by bsouchet          #+#    #+#             */
/*   Updated: 2017/04/28 20:07:10 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		draw_dimensions_parameter(t_rt *rt, t_obj *o)
{
	if (o->forme == T_PLANE || o->forme == T_CUBE)
		draw_parameter(rt, ft_dtoa(o->width), rt->ui->obj_b_rect[6], 2);
	else
		draw_parameter(rt, ft_strf("-----"), rt->ui->obj_b_rect[6], 1);
	if (o->forme == T_CUBE || o->forme == T_CYLINDER || o->forme == T_CONE)
		draw_parameter(rt, ft_dtoa(o->height), rt->ui->obj_b_rect[7], 2);
	else
		draw_parameter(rt, ft_strf("-----"), rt->ui->obj_b_rect[7], 1);
	if (o->forme == T_PLANE || o->forme == T_CUBE)
		draw_parameter(rt, ft_dtoa(o->lenght), rt->ui->obj_b_rect[8], 2);
	else
		draw_parameter(rt, ft_strf("-----"), rt->ui->obj_b_rect[8], 1);
}
