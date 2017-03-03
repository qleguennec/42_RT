/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_dimensions_parameters.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 15:02:08 by bsouchet          #+#    #+#             */
/*   Updated: 2017/03/03 20:14:04 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		draw_dimensions_parameter(t_rt *rt, t_obj *o)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp1 = NULL;
	tmp2 = NULL;
	tmp3 = NULL;
	if (o->forme == T_PLANE || o->forme == T_CUBE)
	{
		tmp1 = ft_dtoa(o->lenght);
		tmp2 = ft_dtoa(o->width);
	}
	else
	{
		tmp1 = ft_strf("-----");
		tmp2 = ft_strf("-----");
	}
	if (o->forme == T_CUBE || o->forme == T_CYLINDER ||
	o->forme == T_CONE || o->forme == T_TORUS)
		tmp3 = ft_dtoa(o->height);
	else
		tmp3 = ft_strf("-----");
	draw_parameter(rt, tmp1, rt->ui->obj_b_rect[6], 2);
	draw_parameter(rt, tmp2, rt->ui->obj_b_rect[7], 2);
	draw_parameter(rt, tmp3, rt->ui->obj_b_rect[8], 2);
}
